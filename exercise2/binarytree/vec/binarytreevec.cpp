#include "binarytreevec.hpp"

namespace lasd {

  // NodeVec Implementation
  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& data) {
    element = data;
  }

  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& data) noexcept {
    std::swap(element, data);
  }

  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(const NodeVec& node) {
    element = node.element;
    index = node.index;
  }

  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(NodeVec&& node) noexcept {
    std::swap(element, node.element);
    std::swap(index, node.index);
  }

  template <typename Data>
  const Data &BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return element;
  }

  template <typename Data>
  Data &BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return element;
  }

  template <typename Data>
  inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (2 * index + 1) < parent->size;
  }

  template <typename Data>
  inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return (2 * index + 2) < parent->size;
  }

  template <typename Data>
  const typename BinaryTreeVec<Data>::Node &
  BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if (!HasLeftChild()) {
      throw std::out_of_range("No left child");
    }
    return *(*(parent->tree))[(2 * index + 1)];
  }

  template <typename Data>
  const typename BinaryTreeVec<Data>::Node &
  BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if (!HasRightChild()) {
      throw std::out_of_range("No right child");
    }
    return *(*(parent->tree))[(2 * index + 2)];
  }

  template <typename Data>
  typename BinaryTreeVec<Data>::MutableNode &
  BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if (!HasLeftChild()) {
      throw std::out_of_range("No left child");
    }
    return *(*(parent->tree))[(2 * index + 1)];
  }

  template <typename Data>
  typename BinaryTreeVec<Data>::MutableNode &
  BinaryTreeVec<Data>::NodeVec::RightChild() {
    if (!HasRightChild()) {
      throw std::out_of_range("No right child");
    }
    return *(*(parent->tree))[(2 * index + 2)];
  }

  // BinaryTreeVec Implementation
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& container) {
    size = container.Size();
    tree = new Vector<NodeVec *>(size);
    unsigned long indexTraversal = 0;
    container.Traverse([&](const Data &data) {
      NodeVec *current = new NodeVec(data);
      (*tree)[indexTraversal] = current;
      (*tree)[indexTraversal]->index = indexTraversal;
      (*tree)[indexTraversal]->parent = this;
      indexTraversal++;
    });
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& container) {
    size = container.Size();
    tree = new Vector<NodeVec *>(size);
    unsigned long indexTraversal = 0;
    container.Map([&](Data &data) {
      NodeVec *current = new NodeVec(std::move(data));
      (*tree)[indexTraversal] = current;
      (*tree)[indexTraversal]->index = indexTraversal;
      (*tree)[indexTraversal]->parent = this;
      indexTraversal++;
    });
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& treeVector) {
    size = treeVector.size;
    tree = new Vector<NodeVec *>(size);
    unsigned long indexTraversal = 0;
    treeVector.BreadthTraverse([&](const Data &data) {
      (*tree)[indexTraversal] = new NodeVec(data);
      (*tree)[indexTraversal]->index = indexTraversal;
      (*tree)[indexTraversal]->parent = this;
      indexTraversal++;
    });
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& treeVector) noexcept {
    std::swap(tree, treeVector.tree);
    std::swap(size, treeVector.size);
    for (unsigned long i = 0; i < size; i++) {
      (*tree)[i]->parent = this;
    }
  }

  template <typename Data>
  BinaryTreeVec<Data>::~BinaryTreeVec() {
    Clear();
    delete tree;
  }

  template <typename Data> BinaryTreeVec<Data>&
  BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& treeVec) {
    size = treeVec.size;
    if (tree) {
      tree->Resize(size);
    } else { 
      tree = new Vector<NodeVec *>(size);
    }

    unsigned long i = 0;
    treeVec.BreadthTraverse([&](const Data &data) {
      (*tree)[i] = new NodeVec(data);
      (*tree)[i]->index = i;
      (*tree)[i]->parent = this;
      i++;
    });
    return *this;
  }

  template <typename Data> BinaryTreeVec<Data>&
  BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& treeVector) noexcept {
    std::swap(size, treeVector.size);
    std::swap(tree, treeVector.tree);
    for (unsigned long i = 0; i < size; i++) {
      (*tree)[i]->parent = this;
    }
    for (unsigned long i = 0; i < treeVector.size; i++) {
      (*treeVector.tree)[i]->parent = &treeVector;
    }
    return *this;
  }

  template <typename Data> inline bool
  BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& treeVector) const noexcept {
    if (size != treeVector.size) {
      return false;
    }
    for (unsigned long i = 0; i < size; i++) {
      if ((*tree)[i]->Element() != treeVector.tree[i]->Element()) {
        return false;
      }
    }
    return true;
  }

  template <typename Data> inline bool
  BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& treeVector) const noexcept {
    return !(*this == treeVector);
  }

  template <typename Data> const typename BinaryTreeVec<Data>::Node&
  BinaryTreeVec<Data>::Root() const {
    if (size == 0) {
      throw std::length_error("Empty tree");
    }
    return *(*tree)[0];
  }

  template <typename Data> typename BinaryTreeVec<Data>::MutableNode&
  BinaryTreeVec<Data>::Root() {
    if (size == 0) {
      throw std::length_error("Empty tree");
    }
    return *(*tree)[0];
  }

  template <typename Data> void
  BinaryTreeVec<Data>::Clear() {
    for (unsigned long i = 0; i < size; i++) {
      delete (*tree)[i];
      (*tree)[i] = nullptr;
    }
    delete tree;
    tree = nullptr;
    size = 0;
  }

  template <typename Data> void
  BinaryTreeVec<Data>::BreadthTraverse(TraverseFun function) const {
    for (unsigned long indexTraverse = 0; indexTraverse < size; indexTraverse++) {
      function((*tree)[indexTraverse]->Element());
    }
  }

  template <typename Data> void
  BinaryTreeVec<Data>::BreadthMap(MapFun function) {
    for (unsigned long indexTraverse = 0; indexTraverse < size; indexTraverse++) {
      function((*tree)[indexTraverse]->Element());
    }
  }
}