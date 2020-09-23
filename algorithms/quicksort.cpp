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

int partition(Array& A, int p, int r);

void quick_sort(Array& A, int p, int r) {
	if (r - p > 0) {
		auto q = partition(A, p, r);
		quick_sort(A, p, q-1);
		quick_sort(A, q+1, r);
	}
}

int partition(Array& A, int p, int r) {
	auto pivot = A[r];
	auto i = p - 1;
	for (auto j = p; j < r; j++) {
		if (A[j] < pivot) {
			i++;
			swap(A[j], A[i]);
		}
	}
	swap(A[r], A[i+1]);
	return i+1;
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
	quick_sort(A, 0, A.size()-1);
	cout << A << endl;
}
