namespace lasd {

  // Constructor: Initialize the stack with elements from a traversable container.
  template <typename Data>
  StackLst<Data>::StackLst(const TraversableContainer<Data>& container) : List<Data>(container) {}

  // Constructor: Initialize the stack by moving elements from a mappable container.
  template <typename Data>
  StackLst<Data>::StackLst(MappableContainer<Data>&& container) : List<Data>(std::move(container)) {}

  // Copy constructor: Initializes a new stack as a deep copy of another stack.
  template <typename Data>
  StackLst<Data>::StackLst(const StackLst<Data>& stack) : List<Data>(stack) {}

  // Move constructor: Initializes a new stack by moving data from another stack.
  template <typename Data>
  StackLst<Data>::StackLst(StackLst<Data>&& stack) : List<Data>(std::move(stack)) {}

  // Copy assignment operator: Assigns a stack using deep copy.
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stack) {
    if (this != &stack) { // Prevent self-assignment
      List<Data>::operator=(stack);
    }
    return *this;
  }

  // Move assignment operator: Assigns a stack using move semantics.
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stack) noexcept {
    if (this != &stack) { // Prevent self-assignment
      List<Data>::operator=(std::move(stack));
    }
    return *this;
  }

  // Equality operator: Compares two stacks for equality.
  template <typename Data>
  inline bool StackLst<Data>::operator==(const StackLst<Data>& stack) const noexcept {
    return List<Data>::operator==(stack);
  }

  // Inequality operator: Compares two stacks for inequality.
  template <typename Data>
  inline bool StackLst<Data>::operator!=(const StackLst<Data>& stack) const noexcept {
    return List<Data>::operator!=(stack);
  }

  // Returns the top element of the stack without removing it.
  template <typename Data>
  inline const Data& StackLst<Data>::Top() const {
    if (!this->size) {
      throw std::length_error("Stack is empty");
    }
    return List<Data>::Front();
  }

  // Returns the top element of the stack without removing it (modifiable version).
  template <typename Data>
  inline Data& StackLst<Data>::Top() {
    if (!this->size) {
      throw std::length_error("Stack is empty");
    }
    return List<Data>::Front();
  }

  // Removes the top element from the stack.
  template <typename Data>
  inline void StackLst<Data>::Pop() {
    if (!this->size) {
      throw std::length_error("Stack is empty");
    }
    List<Data>::RemoveFromFront();
  }

  // Returns the top element of the stack and removes it.
  template <typename Data>
  inline Data StackLst<Data>::TopNPop() {
    if (!this->size) {
      throw std::length_error("Stack is empty");
    }
    return List<Data>::FrontNRemove();
  }

  // Adds an element to the top of the stack.
  template <typename Data>
  inline void StackLst<Data>::Push(const Data& data) {
    List<Data>::InsertAtFront(data);
  }

  // Adds an element to the top of the stack using move semantics for efficiency.
  template <typename Data>
  inline void StackLst<Data>::Push(Data&& data) {
    List<Data>::InsertAtFront(std::move(data));
  }
}