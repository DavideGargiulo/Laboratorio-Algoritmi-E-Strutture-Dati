#include <algorithm>
#include <utility>

namespace lasd {

  template <typename Data> inline
  Vector<Data>::Vector(const TraversableContainer<Data>& container) : Vector(container.Size()) {
    unsigned long i = 0;
    container.Traverse([this, &i](const Data &currData) { 
      elements[i++] = currData;
    });
  }

  template <typename Data> inline
  Vector<Data>::Vector(MappableContainer<Data>&& container) : Vector(container.Size()) {
    unsigned long i = 0;
    container.Map([this, &i](Data &currData) { 
      std::swap(elements[i++], currData);
    });
  }

  template <typename Data> inline
  Vector<Data>::Vector(const Vector<Data>& vector) : Vector(vector.size) {
    for (unsigned long i = 0; i < size; ++i) {
      elements[i] = vector.elements[i];
    }
  }

  template <typename Data> inline
  Vector<Data>::Vector(Vector<Data>&& vector) noexcept {
    std::swap(size, vector.size);
    std::swap(elements, vector.elements);
  }

  template <typename Data> inline Vector<Data>&
  Vector<Data>::operator=(const Vector<Data>& vector) {
    Vector<Data> temp{vector};
    std::swap(temp, *this);
    return *this;
  }

  template <typename Data> inline Vector<Data>&
  Vector<Data>::operator=(Vector<Data> &&vector) noexcept {
    std::swap(size, vector.size);
    std::swap(elements, vector.elements);
    return *this;
  }

  template <typename Data> bool
  Vector<Data>::operator==(const Vector<Data> &vector) const noexcept {
    if (size != vector.size) {
      std::cout << "Vector sizes differ: " << size << " vs " << vector.size << std::endl;
      return false;
    }

    for (unsigned long i = 0; i < size; ++i) {
      if (elements[i] != vector.elements[i]) {
          return false;
      }
    }
    return true;
  }

  template <typename Data> inline bool
  Vector<Data>::operator!=(const Vector<Data>& vector) const noexcept {
    return !(*this == vector);
  }

  template <typename Data> inline const Data&
  Vector<Data>::operator[](unsigned long index) const {
    if (index >= size) {
      throw std::out_of_range("This Vector has not that many elements");
    }
    return elements[index];
  }

  template <typename Data> inline Data&
  Vector<Data>::operator[](unsigned long index) {
    if (index >= size) {
      throw std::out_of_range("This Vector has not that many elements");
    }
    return elements[index];
  }

  template <typename Data> inline void
  Vector<Data>::Clear() {
    delete[] elements;
    size = 0;
    elements = nullptr;
  }

  template <typename Data> void
  Vector<Data>::Resize(unsigned long newSize) {
    if (newSize == size) {
        return;
    }

    if (newSize == 0) {
        Clear();
        return;
    }

    Data* newElements = new Data[newSize];

    unsigned long minSize = std::min(size, newSize);

    for (unsigned long i = 0; i < minSize; ++i) {
        std::swap(elements[i], newElements[i]);
    }

    std::swap(elements, newElements);
    delete[] newElements;

    size = newSize;
  }

  template <typename Data> inline const Data&
  Vector<Data>::Front() const {
    if (size != 0) {
      return elements[0];
    }
    throw std::length_error("Vector is empty");
  }

  template <typename Data> inline Data&
  Vector<Data>::Front() {
    if (size != 0) {
      return elements[0];
    }
    throw std::length_error("Vector is empty");
  }

  template <typename Data> inline const Data&
  Vector<Data>::Back() const {
    if (size != 0) {
      return elements[size - 1];
    }
    throw std::length_error("The Vector is empty");
  }

  template <typename Data> inline Data&
  Vector<Data>::Back() {
    if (size != 0) {
      return elements[size - 1];
    }
    throw std::length_error("The Vector is empty");
  }

  template <typename Data> inline SortableVector<Data>&
  SortableVector<Data>::operator=(const SortableVector<Data> &vector) {
    Vector<Data>::operator=(vector);
    return *this;
  }

  template <typename Data> inline SortableVector<Data>&
  SortableVector<Data>::operator=(SortableVector<Data> &&vector) noexcept {
    Vector<Data>::operator=(std::move(vector));
    return *this;
  }
}