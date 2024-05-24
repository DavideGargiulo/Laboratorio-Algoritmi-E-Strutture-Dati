#include "binarytreevec.hpp"

namespace lasd {

  // NodeVec Implementation
  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& data) {
    element = data;
  }

  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& data) noexcept {
    element = std::move(data);
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

  template <typename Data> const Data&
  BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return element;
  }

  template <typename Data> Data&
  BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return element;
  }

  template <typename Data> inline bool
  BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (2 * index + 1) < parent->size;
  }

  template <typename Data> inline bool
  BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return (2 * index + 2) < parent->size;
  }

  template <typename Data> const typename BinaryTreeVec<Data>::Node&
  BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if (!HasLeftChild()) {
      throw std::out_of_range("No left child");
    }
    return *(*(parent->tree))[(2 * index + 1)];
  }

  template <typename Data> const typename BinaryTreeVec<Data>::Node&
  BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if (!HasRightChild()) {
      throw std::out_of_range("No right child");
    }
    return *(*(parent->tree))[(2 * index + 2)];
  }

  template <typename Data> typename BinaryTreeVec<Data>::MutableNode&
  BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if (!HasLeftChild()) {
      throw std::out_of_range("No left child");
    }
    return *(*(parent->tree))[(2 * index + 1)];
  }

  template <typename Data> typename BinaryTreeVec<Data>::MutableNode&
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
    tree = new Vector<NodeVec*>(size);
    ulong indexTraversal = 0;
    container.Traverse([&](const Data& data) {
      NodeVec* current = new NodeVec(data);
      (*tree)[indexTraversal] = current;
      (*tree)[indexTraversal]->index = indexTraversal;
      (*tree)[indexTraversal]->parent = this;
      indexTraversal++;
    });
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& container) {
    size = container.Size();
    tree = new Vector<NodeVec*>(size);
    ulong indexTraversal = 0;
    container.Map([&](Data&& data) {
      NodeVec* current = new NodeVec(data);
      (*tree)[indexTraversal] = current;
      (*tree)[indexTraversal]->index = indexTraversal;
      (*tree)[indexTraversal]->parent = this;
      indexTraversal++;
    });
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& treeVec) {
    size = treeVec.size;
    tree = new Vector<NodeVec*>(size);
    ulong indexTraversal = 0;
    treeVec.BreadthTraverse([&](const Data& data) {
      (*tree)[indexTraversal] = new NodeVec(data);
      (*tree)[indexTraversal]->index = indexTraversal;
      (*tree)[indexTraversal]->parent = this;
      indexTraversal++;
    });
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& treeVec) noexcept {
    std::swap(tree, treeVec.tree);
    std::swap(size, treeVec.size);
  }

  template <typename Data>
  BinaryTreeVec<Data>::~BinaryTreeVec() {
    Clear();
    delete tree;
  }

  template <typename Data> BinaryTreeVec<Data>&
  BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& treeVec) {
    if (this != &treeVec) {
      delete[] tree;

      size = treeVec.size;

      tree = new Vector<NodeVec*>(size);

      for (ulong i = 0; i < size; i++) {
        (*tree)[i] = new NodeVec(*treeVec.tree->operator[](i));
        (*tree)[i]->index = i;
        (*tree)[i]->parent = this;
      }
    }

    return *this;
  }

  template <typename Data> BinaryTreeVec<Data>&
  BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& treeVec) noexcept {
    if (this != &treeVec) {
      std::swap(size, treeVec.size);
      std::swap(tree, treeVec.tree);
    }
    return *this;
  }

  template <typename Data> inline bool
  BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& treeVec) const noexcept {
    if (size != treeVec.size) {
      return false;
    }
    for (ulong i = 0; i < size; i++) {
      if ((*tree)[i]->Element() != treeVec.tree[i]->Element()) {
        return false;
      }
    }
    return true;
  }

  template <typename Data> inline bool
  BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& treeVec) const noexcept {
    return !(*this == treeVec);
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
    for (ulong i = 0; i < size; i++) {
      delete (*tree)[i];
      (*tree)[i] = nullptr;
    }
    delete tree;
    tree = nullptr;
    size = 0;
  }

  template <typename Data> void
  BinaryTreeVec<Data>::BreadthTraverse(TraverseFun function) const {
    for (ulong indexTraverse = 0; indexTraverse < size; indexTraverse++) {
      function((*tree)[indexTraverse]->Element());
    }
  }

  template <typename Data> void
  BinaryTreeVec<Data>::BreadthMap(MapFun function) {
    for (ulong indexTraverse = 0; indexTraverse < size; indexTraverse++) {
      function((*tree)[indexTraverse]->Element());
    }
  }
}