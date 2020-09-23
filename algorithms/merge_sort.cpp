#include <iostream>
#include <vector>
#include <limits>

using namespace std;
using Array = vector<int>;

void merge(Array& A, int p, int q, int r);

void merge_sort(Array& A, int p, int r) {
	if (r - p > 1) {
		int q = (r+p)/2;
		merge_sort(A, p, q);
		merge_sort(A, q, r);
		merge(A, p, q, r);
	}
}

void merge(Array& A, int p, int q, int r) {
	auto n1 = q - p;
	auto n2 = r - q;
	Array L(n1+1);
	for (auto i = 0; i < n1; i++) {
		L[i] = A[p + i];
	}
	Array R(n2+1);
	for (auto i = 0; i < n2; i++) {
		R[i] = A[q + i];
	}
	L[n1] = numeric_limits<int>::max();
	R[n2] = numeric_limits<int>::max();
	int i = 0;
	int j = 0;
	for (auto k = p; k < r; k++) {
		if (L[i] < R[j]) {
			A[k] = L[i];
			i++;
		}	else {
			A[k] = R[j];
			j++;
		}
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
	merge_sort(A, 0, A.size());
	cout << A << endl;
}
