#include "list.hpp"
#include <iostream>

int main() {
  custom::list<int> l {1,2};
  // l.push_back(1);  
  l.push_back(4);  
  std::cout << *(l.begin()) << std::endl;
  std::cout << l.size() << std::endl;
  for (auto x : l) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
  l.erase(l.begin());
  std::cout << *(l.begin()) << std::endl;
  std::cout << l.size() << std::endl;
  for (auto x : l) {
    std::cout << x << ' ';
  }
}