#include <iostream>
#include <vector>

using namespace std;
using Array = vector<int>;

void bubble_sort(Array& A) {
	for (auto i = 1; i < A.size(); i++) {
		for (auto j = A.size()-1; j >= i; j--){
			if (A[j] < A[j-1]) {
				auto tmp = A[j];
				A[j] = A[j-1];
				A[j-1] = tmp;
			}
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
	bubble_sort(A);
	cout << A << endl;
}
