#include "test_runner.h"
#include "profile.h"
#include "concurrent_map.h"

#include <algorithm>
#include <future>
#include <numeric>
#include <random>
#include <string>

using namespace std;

void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, 
		size_t thread_count, 
		int key_count,
		int update_count
) {
  auto kernel = [&cm, key_count, update_count](int seed) {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));
    for (int i = 0; i < update_count; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  vector<future<void>> futures;
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const size_t thread_count = 3;
  const size_t key_count = 50000;
  const size_t update_count = 10;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count, update_count);

  const auto result = cm.BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count);
  for (auto& [k, v] : result) {
    AssertEqual(v, thread_count*update_count, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader = [&cm] {
    vector<string> result(50000);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = async(updater);
  auto r1 = async(reader);
  auto u2 = async(updater);
  auto r2 = async(reader);

  u1.get();
  u2.get();

  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeed( size_t lock_count,
								size_t thread_count,
  							size_t key_count,
							  size_t update_count ) 
{
	ConcurrentMap<int, int> single_lock(lock_count);

	LOG_DURATION(to_string(lock_count) + " locks, " + 
			to_string(thread_count) + " threads");
	RunConcurrentUpdates(single_lock, thread_count, key_count, update_count);
}

void TestSpeedup() {
  const size_t thread_count = 4;
  const size_t key_count = 50000;
  const size_t update_count = 4;
	const size_t total_updates = thread_count * update_count;

	TestSpeed(1, 1, key_count, total_updates / 1);
	TestSpeed(1, 4, key_count, total_updates / 4);
	TestSpeed(100, 4, key_count, total_updates / 4);
	TestSpeed(1000, 2, key_count, total_updates / 2);
	TestSpeed(1000, 4, key_count, total_updates / 4);
	TestSpeed(1000, 8, key_count, total_updates / 8);
	TestSpeed(10000, 4, key_count, total_updates / 4);
}

void TestStringKey() {
	ConcurrentMap<string, int> m(10);
	m["abc"].ref_to_value = 1;
	AssertEqual(m.At("abc").ref_to_value, 1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestReadAndWrite);
  RUN_TEST(tr, TestSpeedup);
  RUN_TEST(tr, TestStringKey);
}
