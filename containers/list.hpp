#include <stddef.h>
#include <initializer_list>

#include "list_iterator.hpp"

namespace custom {
  template<typename T>
  class list {
  private:
    struct Node {
      T val;
      Node* next = nullptr;
      Node* prev = nullptr;
    };

    size_t size_ = 0;
    Node* root = nullptr;
    Node* last = nullptr;
  public:
    explicit list() = default;
    explicit list(size_t n);
    explicit list(size_t n, const T& val);
    list(std::initializer_list<T> il);

    class reverse_iterator {};
    class const_iterator {};
    class const_reverse_iterator {};
    // assign();
    friend iterator<T, list<T>>;
    friend const_iterator;

    iterator<T,list<T>> begin();
    const_iterator begin() const;
    iterator<T,list<T>> end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    // const_iterator cbegin() const;
    // const_iterator cend() const;
    // const_reverse_iterator crbegin() const;
    // const_reverse_iterator crend() const;
    
    T& back();
    T& front();
    const T& back() const;
    const T& front() const;
    
    iterator<T,list<T>> insert(const_iterator position, const T& val);
    // other 4 inserts

    void push_back(const T& val);
    void push_back(T&& val);
    void push_front(const T& val);
    void push_front(T&& val);

    bool empty() const;
    size_t size() const;
    void clear();

    iterator<T,list<T>> erase(iterator<T,list<T>> position);

    ~list() {
      clear();
    }

    // emplace();
    // emplace_back();
    // emplace_front();
    // get_allocator();
    // max_size();
    // merge();
    // operator=();
    // pop_back();
    // pop_front();
    // remove();
    // remove_if();
    // resize();
    // reverse();
    // sort();
    // splice();
    // swap();
    // unique();
  };
  

  // Implementation
  
  template<typename T>
  list<T>::list(size_t n) {
    for (size_t i = 0; i < n; i++) {
      push_back(T());
    }
  }

  template<typename T>
  list<T>::list(size_t n, const T& val) {
    for (size_t i = 0; i < n; i++) {
      push_back(val);
    }
  }
  
  template<typename T>
  list<T>::list(std::initializer_list<T> il) {
    for (auto& x : il) {
      push_back(x);
    }
  }
    
  template<typename T>
  void list<T>::push_back(const T& val) {
    Node* p = new Node{val};
    if (last) {
      last->next = p;
    } else {
      root = p;
    }
    last = p;
    size_ += 1;
  }

  template<typename T>
  void list<T>::push_back(T&& val) {
    Node* p = new Node{val};
    if (last) {
      last->next = p;
    } else {
      root = p;
    }
    last = p;
    size_ += 1;
  }

  template<typename T>
  void list<T>::push_front(const T& val) {
    Node* p = new Node(val);
    if (root) {
      root->prev = p;
    } else {
      last = p;
    }
    root = p;
    size_ += 1;
  }

  template<typename T>
  T& list<T>::front() {
    return *root; // UB in case of empty list
  }
  template<typename T>
  const T& list<T>::front() const {
    return *root; // UB in case of empty list
  }
  template<typename T>
  T& list<T>::back() {
    return *last; // UB in case of empty list
  }
  template<typename T>
  const T& list<T>::back() const {
    return *last; // UB in case of empty list
  }

  template<typename T>
  size_t list<T>::size() const {
    return size_;
  }
  template<typename T>
  bool list<T>::empty() const {
    return size_==0;
  }

  template<typename T>
  iterator<T, list<T>> list<T>::erase(iterator<T,list<T>> position) {
    auto prev = position.current->prev;
    auto next = position.current->next;
    auto current = position.current;
    if (prev) {
      prev->next = next;
    } else {
      root = next;
    }
    if (next) {
      next->prev = prev;
    } else {
      last = prev;
    }
    size_ -= 1;
    auto next_it = ++position;
    if (current){
      delete current;
    }
    return next_it;
  }

  template<typename T>
  iterator<T,list<T>> list<T>::begin() {
    return {root, *this};
  }

  template<typename T>
  iterator<T,list<T>> list<T>::end() {
    return {nullptr, *this};
  }

  template<typename T>
  void list<T>::clear() {
    auto it = begin();
    while (it != end()) {
      it = erase(it);
    }
  }
}