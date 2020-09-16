
namespace custom {
  template<typename T>
  class list;
  
  template<typename T, class Container=list<T>>
  class iterator {
    using Node = typename Container::Node;
    Node* current;
    const Container* container;

    iterator(Node* c, const Container& l) : current(c), container(&l) {}
    friend list<T>;
  public:
    iterator& operator=(const iterator& other);
    
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    
    Node* operator->() { return current; }
    T& operator*() { return current->val; }
    bool operator!=(const iterator& other) { return current!=other.current; }
    bool operator==(const iterator& other) { return current==other.current; }
  };
  
  // Implementation

  template<typename T, class Container>
  iterator<T,Container>& iterator<T,Container>::operator++(){
    if (current) {
      current = current->next;
    } else {
      current = container->root;
    }
    return *this;
  }

  template<typename T, class Container>
  iterator<T, Container> iterator<T,Container>::operator++(int){
    auto temp = *this;
    if (current) {
      current = current->next;
    } else {
      current = container->root;
    }
    return temp;
  }
  
  template<typename T, class Container>
  iterator<T,Container>& iterator<T,Container>::operator--(){
    if (current) {
      current = current->prev;
    } else {
      current = container->last;
    }
    return *this;
  }

  template<typename T, class Container>
  iterator<T, Container> iterator<T,Container>::operator--(int){
    auto temp = *this;
    if (current) {
      current = current->prev;
    } else {
      current = container->last;
    }
    return temp;
  }
  
  template<typename T, class Container>
  iterator<T, Container>& iterator<T,Container>::operator=(const iterator<T,Container>& other){
    current = other.current;
    container = other.container;
    return *this;
  }
}