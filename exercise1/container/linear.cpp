#include <algorithm>

namespace lasd {

  template <typename Data> bool
  LinearContainer<Data>::operator==(const LinearContainer<Data>& container) const noexcept {
    if (size != container.size) {
        return false;
    }

    for (unsigned long i = 0; i < size; ++i) {
        if ((*this)[i] != container[i]) {  // Using the subscript operator to access elements
            return false;
        }
    }
    return true;
  }


  template <typename Data> inline const Data& 
  LinearContainer<Data>::Front() const {
    if (this->size == 0) {
      throw std::length_error("Container is empty.");
    }
    return (*this)[0];
  }

  template <typename Data> inline Data& 
  LinearContainer<Data>::Front() {
    if (this->size != 0) {
      throw std::length_error("Container is empty.");
    }
    return (*this)[0];
  }

  template <typename Data>
  inline const Data &LinearContainer<Data>::Back() const {
    if (this->size == 0) {
      throw std::length_error("Container is empty.");
    }
    return (*this)[this->size - 1];
  }

  template <typename Data> inline Data& 
  LinearContainer<Data>::Back() {
    if (this->size == 0) {
      throw std::length_error("Container is empty.");
    }
    return (*this)[this->size - 1];
  }

  template <typename Data> void 
  LinearContainer<Data>::PreOrderTraverse(const TraverseFun function) const {
    for (unsigned long i = 0; i < this->size; ++i) {
      function((*this)[i]);
    }
  }

  template <typename Data> void 
  LinearContainer<Data>::PostOrderTraverse(const TraverseFun function) const {
    for (unsigned long i = this->size; i-- > 0; ) {
        function((*this)[i]);
    }
  }

  template <typename Data> void 
  LinearContainer<Data>::PreOrderMap(MapFun function) {
    for (unsigned long i = 0; i < this->size; i++) {
      function((*this)[i]);
    }
  }

  template <typename Data> void 
  LinearContainer<Data>::PostOrderMap(MapFun function) {
    for (unsigned long i = this->size; i-- > 0; ) {
        function((*this)[i]);
    }
  }

  template <typename Data>
  void SortableLinearContainer<Data>::quickSort(unsigned long low, unsigned long high) noexcept {
      if (low < high) {
          unsigned long pivotIndex = partition(low, high);
          if (pivotIndex != 0) {
              quickSort(low, pivotIndex - 1);
          }
          quickSort(pivotIndex + 1, high);
      }
  }

  template <typename Data> unsigned long 
  SortableLinearContainer<Data>::partition(unsigned long low, unsigned long high) noexcept {
    // Scegli il primo elemento come pivot
    const Data& pivot = (*this)[low];

    unsigned long left = low;
    unsigned long right = high + 1;

    while (true) {
        // Trova l'elemento più grande a sinistra del pivot
        do {
            ++left;
        } while (left <= high && (*this)[left] < pivot);

        // Trova l'elemento più piccolo a destra del pivot
        do {
            --right;
        } while ((*this)[right] > pivot);

        // Se i puntatori si incrociano, la partizione è completa
        if (left >= right) {
            break;
        }

        // Scambia gli elementi
        std::swap((*this)[left], (*this)[right]);
    }

    // Sposta il pivot nella sua posizione finale
    std::swap((*this)[low], (*this)[right]);
    return right;
  }
}