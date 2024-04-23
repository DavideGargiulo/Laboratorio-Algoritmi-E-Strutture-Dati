namespace lasd {

  // Default constructor: Creates an empty stack with initial capacity.
  template <typename Data>
  StackVec<Data>::StackVec() : Vector<Data>(INITIAL_CAPACITY) {}

  // Constructor taking a traversable container: Initializes the stack with the elements of the provided container.
  template <typename Data>
  StackVec<Data>::StackVec(const TraversableContainer<Data>& container) : Vector<Data>::Vector(container) {
    topIndex = Vector<Data>::Size();
    if (topIndex < INITIAL_CAPACITY) {
      this->Resize(INITIAL_CAPACITY);
    }
  }

  // Constructor taking a mappable container: Initializes the stack with the elements of the provided container.
  template <typename Data>
  StackVec<Data>::StackVec(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)) {
    topIndex = Vector<Data>::Size();
    if (topIndex < INITIAL_CAPACITY) {
      this->Resize(INITIAL_CAPACITY);
    }
  }

  // Copy constructor: Initializes the stack as a copy of another stack.
  template <typename Data>
  StackVec<Data>::StackVec(const StackVec<Data>& stack) : Vector<Data>(stack), topIndex(stack.topIndex) {}

  // Move constructor: Initializes the stack by moving the contents of another stack.
  template <typename Data>
  StackVec<Data>::StackVec(StackVec<Data>&& stack) noexcept : Vector<Data>(std::move(stack)) {
    std::swap(topIndex, stack.topIndex);
  }

  // Copy assignment operator: Assigns the contents of another stack to this stack.
  template <typename Data> inline StackVec<Data>&
  StackVec<Data>::operator=(const StackVec<Data>& stack) {
    if (this != &stack) {
      Vector<Data>::operator=(stack);
      topIndex = stack.topIndex;
    }
    return *this;
  }

  // Move assignment operator: Assigns the contents of another stack to this stack by moving.
  template <typename Data>
  inline StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stack) noexcept {
    if (this != &stack) {
      Vector<Data>::operator=(std::move(stack));
      topIndex = stack.topIndex;
      stack.topIndex = 0;
    }
    return *this;
  }

  // Equality operator: Checks if two stacks are equal in size and content.
  template <typename Data> inline bool
  StackVec<Data>::operator==(const StackVec<Data>& stack) const noexcept{
    if (topIndex != stack.topIndex) {
      return false;
    }

    for (std::size_t i = 0; i < topIndex; i++) {
      if ((*this)[i] != stack[i]) {
        return false;
      }
    }
    return true;
  }

  // Inequality operator: Checks if two stacks are not equal in size or content.
  template <typename Data> inline bool
  StackVec<Data>::operator!=(const StackVec<Data>& stack) const noexcept {
    return !(*this == stack);
  }

  // Retrieve the top element of the stack (const version).
  template <typename Data> inline const Data&
  StackVec<Data>::Top() const {
    if (!topIndex) {
      throw std::length_error("Stack is empty");
    }
    return (*this)[topIndex - 1];
  }

  // Retrieve the top element of the stack (non-const version).
  template <typename Data> inline Data&
  StackVec<Data>::Top() {
    if (!topIndex) {
      throw std::length_error("Stack is empty");
    }
    return (*this)[topIndex - 1];
  }

  // Remove the top element from the stack.
  template <typename Data> inline void
  StackVec<Data>::Pop() {
    if (!topIndex) {
      throw std::length_error("Stack is empty");
    }
    --topIndex;

    if (topIndex < size / REDUCTION_THRESHOLD) {
      Resize(size / REDUCTION_FACTOR);
    }
  }

  // Retrieve the top element of the stack and then remove it.
  template <typename Data> inline Data
  StackVec<Data>::TopNPop() {
    Data topElement = std::move(Top());
    Pop();
    return topElement;
  }

  // Push an element onto the top of the stack.
  template <typename Data> inline void
  StackVec<Data>::Push(const Data& data) {
    if (topIndex == size) {
      Resize(size * EXPANSION_FACTOR);
    }
    (*this)[topIndex] = data;
    ++topIndex;
  }

  // Move version of the Push function.
  template <typename Data> inline void
  StackVec<Data>::Push(Data&& data) {
    if (topIndex == size) {
      Resize(size * EXPANSION_FACTOR);
    }
    (*this)[topIndex] = std::move(data);
    ++topIndex;
  }

  // Clear the stack, making it empty.
  template <typename Data> inline void
  StackVec<Data>::Clear() {
    Resize(INITIAL_CAPACITY);
    topIndex = 0;
  }

  // Resize the underlying vector, ensuring that its size does not go below the initial capacity.
  template <typename Data> inline void
  StackVec<Data>::Resize(unsigned long size) {
    if (size > INITIAL_CAPACITY) {
      Vector<Data>::Resize(size);
    }
  }
}