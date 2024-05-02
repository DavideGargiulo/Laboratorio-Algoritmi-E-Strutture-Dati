#include <algorithm>
#include <memory>

namespace lasd {

  template <typename Data>
  QueueVec<Data>::QueueVec() : Vector<Data>::Vector(INITIAL_CAPACITY) {}

  // Copy constructor from Different DataStructures
  template <typename Data>
  QueueVec<Data>::QueueVec(const TraversableContainer<Data> &con) : Vector<Data>::Vector(con), tail(con.Size()), numElements(con.Size()) {
    if (size < INITIAL_CAPACITY)
      Resize(INITIAL_CAPACITY);
  }

  // Move constructor from Different DataStructures
  template <typename Data>
  QueueVec<Data>::QueueVec(MappableContainer<Data> &&con) : Vector<Data>::Vector(std::move(con)), tail(con.Size()), numElements(con.Size()) {
    if (size < INITIAL_CAPACITY )
      Resize(INITIAL_CAPACITY );
  }

  template <typename Data>
  QueueVec<Data>::QueueVec(const QueueVec<Data>& queue) {
    static_cast<Vector<Data>&>(*this) = static_cast<const Vector<Data>&>(queue);

    head = queue.head;
    tail = queue.tail;
    numElements = queue.numElements;
  }

  template <typename Data>
  QueueVec<Data>::QueueVec(QueueVec<Data>&& queue) noexcept : Vector<Data>::Vector(std::move(queue)) {
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);
    std::swap(numElements, queue.numElements);
  }

  template <typename Data> inline QueueVec<Data>&
  QueueVec<Data>::operator=(const QueueVec<Data>& queue) {
    if (this != &queue) {
      static_cast<Vector<Data>&>(*this) = static_cast<const Vector<Data>&>(queue);

      head = queue.head;
      tail = queue.tail;
      numElements = queue.numElements;
    }
    return *this;
  }

  template <typename Data> inline QueueVec<Data>&
  QueueVec<Data>::operator=(QueueVec<Data>&& queue) noexcept {
    if (this != &queue) {
      static_cast<Vector<Data>&>(*this) = static_cast<const Vector<Data>&>(queue);

      head = queue.head;
      tail = queue.tail;
      numElements = queue.numElements;
    }
    return *this;
  }

  template <typename Data> inline bool
  QueueVec<Data>::operator==(const QueueVec<Data>& queue) const noexcept {
    if (numElements != queue.numElements) {
      return false;
    }

    for (unsigned long i = 0; i < numElements; ++i) {
      if (elements[(head + i) % size] != queue.elements[(queue.head + i) % queue.size]) {
        return false;
      }
    }

    return true;
  }


  template <typename Data> inline bool
  QueueVec<Data>::operator!=(const QueueVec<Data>& queue) const noexcept {
    return !(*this == queue);
  }

  template <typename Data> inline const Data&
  QueueVec<Data>::Head() const {
    if (!numElements) {
      throw std::length_error("Queue is empty");
    }
    return elements[head];
  }

  template <typename Data> inline Data&
  QueueVec<Data>::Head() {
    if (!numElements) {
      throw std::length_error("Queue is empty");
    }
    return elements[head];
  }

  template <typename Data> inline void
  QueueVec<Data>::Dequeue() {
    if (!numElements) {
      throw std::length_error("Queue is empty");
    }
    head = (head + 1) % size;
    --numElements;

    if (numElements > 0 && numElements == size / REDUCTION_THRESHOLD) {
      this->Resize(size / REDUCTION_FACTOR);
    }
  }

  template <typename Data> inline Data
  QueueVec<Data>::HeadNDequeue() {
    if (!numElements) {
      throw std::length_error("Queue is empty");
    }
    Data data = Head();
    Dequeue();
    return data;
  }

  template <typename Data> inline void
  QueueVec<Data>::Enqueue(const Data& data) {
    if (numElements == size) {
      this->Resize(size * EXPANSION_FACTOR);
    }

    elements[tail] = data;
    tail = (tail + 1) % size;
    ++numElements;
  }

  template <typename Data> inline void
  QueueVec<Data>::Enqueue(Data&& data) {
    if (numElements == size) {
      this->Resize(size * EXPANSION_FACTOR);
    }

    elements[tail] = data;
    tail = (tail + 1) % size;
    ++numElements;
  }

  template <typename Data> inline bool
  QueueVec<Data>::Empty() const noexcept {
    return !numElements;
  }

  template <typename Data> inline unsigned long
  QueueVec<Data>::Size() const noexcept {
    return numElements;
  }

  template <typename Data> inline void
  QueueVec<Data>::Clear() {
    head = 0;
    tail = 0;
    numElements = 0;
    Resize(INITIAL_CAPACITY);
  }

  template <typename Data> inline void
  QueueVec<Data>::Resize(unsigned long newSize) {
    if (newSize < INITIAL_CAPACITY || newSize == size || newSize < numElements) {
      return;
    }

    std::unique_ptr<Data[]> temp(new Data[newSize]{});
    for (unsigned long i = head, j = 0; j < numElements; i = (i + 1) % size, ++j) {
      temp[j] = std::move(elements[i]);
    }

    delete[] elements;

    elements = temp.release();
    head = 0;
    tail = numElements;
    size = newSize;
  }
}