namespace lasd {

  // Constructor taking a traversable container: Initializes the queue with the elements of the provided container.
  template <typename Data>
  QueueLst<Data>::QueueLst(const TraversableContainer<Data>& container) : List<Data>(container) {}

  // Constructor taking a mappable container: Initializes the queue with the elements of the provided container.
  template <typename Data>
  QueueLst<Data>::QueueLst(MappableContainer<Data>&& container) : List<Data>(std::move(container)) {}

  // Copy constructor: Initializes the queue as a copy of another queue.
  template <typename Data>
  QueueLst<Data>::QueueLst(const QueueLst<Data>& queue) : List<Data>::List(queue) {}

  // Move constructor: Initializes the queue by moving the contents of another queue.
  template <typename Data>
  QueueLst<Data>::QueueLst(QueueLst<Data>&& queue) noexcept : List<Data>::List(std::move(queue)) {}

  // Copy assignment operator: Assigns the contents of another queue to this queue.
  template <typename Data> inline QueueLst<Data>&
  QueueLst<Data>::operator=(const QueueLst<Data>& queue) {
    if (this != &queue) {
      List<Data>::operator=(queue);
    }
    return *this;
  }

  // Move assignment operator: Assigns the contents of another queue to this queue by moving.
  template <typename Data> inline QueueLst<Data>&
  QueueLst<Data>::operator=(QueueLst<Data>&& queue) noexcept {
    if (this != &queue) {
      List<Data>::operator=(std::move(queue));
    }
    return *this;
  }

  // Equality operator: Checks if two queues are equal in size and content.
  template <typename Data> inline bool
  QueueLst<Data>::operator==(const QueueLst<Data>& queue) const noexcept {
    return List<Data>::operator==(queue);
  }

  // Inequality operator: Checks if two queues are not equal in size or content.
  template <typename Data> inline bool
  QueueLst<Data>::operator!=(const QueueLst<Data>& queue) const noexcept {
    return !(*this == queue);
  }

  // Retrieve the element at the front of the queue (const version).
  template <typename Data> inline const Data&
  QueueLst<Data>::Head() const {
    if (!this->size) {
      throw std::length_error("Queue is empty");
    }
    return List<Data>::Front();
  }

  // Retrieve the element at the front of the queue (non-const version).
  template <typename Data> inline Data&
  QueueLst<Data>::Head() {
    if (!this->size) {
      throw std::length_error("Queue is empty");
    }
    return List<Data>::Front();
  }

  // Remove the element at the front of the queue.
  template <typename Data> inline void
  QueueLst<Data>::Dequeue() {
    if (!this->size) {
      throw std::length_error("Queue is empty");
    }
    List<Data>::RemoveFromFront();
  }

  // Retrieve the element at the front of the queue and then remove it.
  template <typename Data> inline Data
  QueueLst<Data>::HeadNDequeue() {
    if (!this->size) {
      throw std::length_error("Queue is empty");
    }
    return List<Data>::FrontNRemove();
  }

  // Insert an element at the back of the queue.
  template <typename Data> inline void
  QueueLst<Data>::Enqueue(const Data& value) {
    List<Data>::InsertAtBack(value);
  }

  // Move version of the Enqueue method: Inserts an element at the back of the queue by moving.
  template <typename Data> inline void
  QueueLst<Data>::Enqueue(Data&& value) {
    List<Data>::InsertAtBack(std::move(value));
  }
}