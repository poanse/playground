#include <iostream>
#include <vector>
#include <limits>

using namespace std;
using Array = vector<int>;

void swap(int& a, int& b) {
	int tmp = b;
	b = a;
	a = tmp;
}

int left(int i) {
	return 2 * i;
}
int right(int i) {
	return 2 * i + 1;
}

void max_heapify(Array& A, int i, size_t heap_size) {
	auto l = left(i);
	auto r = right(i);
	int largest = i;
	if (A[l] > A[i] && l < heap_size) {
		largest = l;
	}
	if (A[r] > A[largest] && r < heap_size) {
		largest = r;
	}
	if (largest != i) {
		swap(A[i], A[largest]);
		max_heapify(A, largest, heap_size);
	}
}

void build_max_heap(Array& A) {
	for (auto i = A.size() / 2; i >= 0; i--) {
		max_heapify(A, i, A.size());
	}
}

void heap_sort(Array& A) {
	build_max_heap(A);
	heap_size = A.size();
	for (auto j = A.size()-1; j > 0; j--) {
		swap(A[0], A[j]);
		heap_size--;
		max_heapify(A, 0, heap_size);
	}
}

ostream& operator<< (ostream& os, const Array& A) {
	for (auto i = 0; i+1 < A.size(); i++) {
		os << A[i] << ' ';
	}
	os << A[A.size()-1];
	return os;
}

int main() {
	Array A {1,5,3,7,7,9,0};
	cout << A << endl;
	heap_sort(A, 0, A.size()-1);
	cout << A << endl;
}
