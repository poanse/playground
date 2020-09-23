#include <iostream>
#include <vector>
#include <limits>

using namespace std;
using Array = vector<int>;

ostream& operator<< (ostream& os, const Array& A) {
	for (auto i = 0; i+1 < A.size(); i++) {
		os << A[i] << ' ';
	}
	os << A[A.size()-1];
	return os;
}

int binary_search(const Array& A, int val) {
	int L = 0;
	int R = A.size() - 1;
	while (L < R) {
		int m = (L + R) / 2;
		if (A[m] < val) {
			L = m + 1;
		} else {
			R = m;
		}
	}
	if (A[L] == val) {
		return L;
	}
	return -1;
}

int binary_search_rec(const Array& A, int val, size_t L, size_t R) {
	if (L == R) {
		if (A[L] == val) {
			return L;
		}
		return -1;
	}
	size_t m = (L + R) / 2;
	if (A[m] < val) {
		return binary_search_rec(A, val, m + 1, R);
	}
	return binary_search_rec(A, val, L, m);
}

int main() {
	Array A {0,1,3,5,7,7,9};
	cout << "Array:" << A << endl;
	cout << "Binary search of 5: " << binary_search(A, 5) << '\n';
	cout << "Recursive binary search of 5: " 
		<< binary_search_rec(A, 5, 0, A.size()-1);
}
