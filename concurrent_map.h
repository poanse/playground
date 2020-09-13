#pragma once

#include <vector>
#include <mutex>
#include <unordered_map>

template <typename K, typename V>
using container = std::unordered_map<K, V>;

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap {
private:
	mutable std::vector<std::mutex> mutexes;
	std::vector<container<K, V>> maps;
	Hash hasher;
public:
	template <typename T>
  struct Access {
		std::lock_guard<std::mutex> lock;
    V& ref_to_value;
  };

	template <typename T>
  struct AccessC {
		std::lock_guard<std::mutex> lock;
    const V& ref_to_value;
  };

  explicit ConcurrentMap(const size_t bucket_count)
		: mutexes(bucket_count)
		,	maps(bucket_count) 
	{
	}

	size_t GetMapIndex(const K key) const {
		return hasher(key) % maps.size();
	}

	bool Has(const K& key) const {
		auto idx = GetMapIndex(key);
		std::lock_guard<std::mutex> lock(mutexes[idx]);
		return maps[idx].count(key);
	}

	AccessC<V> At(const K& key) const {
		auto idx = GetMapIndex(key);
		return {std::lock_guard<std::mutex>(mutexes[idx]), 
			maps[idx].at(key)};
	}

  Access<V> operator[](const K& key) {
		auto idx = GetMapIndex(key);
		return {std::lock_guard<std::mutex>(mutexes[idx]), 
			maps[idx][key]};
	}

  std::unordered_map<K, V, Hash> BuildOrdinaryMap() const {
		std::unordered_map<K, V, Hash> result;
		for (size_t i = 0; i < maps.size(); i++) {
			std::lock_guard<std::mutex> lock(mutexes[i]);
			result.insert(maps[i].begin(), maps[i].end());
		}
		return result;
	}
};
