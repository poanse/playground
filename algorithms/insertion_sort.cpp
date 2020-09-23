#include <iostream>
#include <vector>

using namespace std;
using Array = vector<int>;

void insertion_sort(Array& A) {
	for (auto j = 1; j < A.size(); j++) {
		auto key = A[j];
		int i = j-1;
		for (; i > -1 && A[i] > key; i--) {
			A[i+1] = A[i];
		}
		A[i+1] = key;
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
	insertion_sort(A);
	cout << A << endl;
}
