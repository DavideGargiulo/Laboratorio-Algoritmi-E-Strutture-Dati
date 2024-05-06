namespace lasd {
  
  template <typename Data> inline bool
  BinaryTree<Data>::Node::operator==(const Node& node) const noexcept {
    if (node.Element() != this->Element()) {
      return false;
    }

    bool hasRight = this->HasRightChild();
    bool hasLeft = this->HasLeftChild();

    if (hasRight != node.HasRightChild() || hasLeft != node.HasLeftChild()) {
      return false;
    }

    bool leftEqual = hasLeft ? (node.LeftChild() == this->LeftChild()) : true;
    bool rightEqual = hasRight ? (node.RightChild() == this->RightChild()) : true;

    return leftEqual && rightEqual;
  }

  template <typename Data> inline bool
  BinaryTree<Data>::operator==(const BinaryTree<Data>& otherTree) const noexcept {
    if (size == otherTree.size) {
      if (size != 0) {
        return Root() == otherTree.Root();
      } else {
        return true;
      }
    } else {
      return false;
    }
  }

  template <typename Data> void
  BinaryTree<Data>::PreOrderTraverse(Node* node, TraverseFun function) const {
    if (node == nullptr) {
      return;
    }

    function(node->Element());
    PreOrderTraverse(node->LeftChild(), function);
    PreOrderTraverse(node->RightChild(), function);
  }

  template <typename Data> void
  BinaryTree<Data>::PostOrderTraverse(Node* node, TraverseFun function) const {
    if (node == nullptr) {
      return;
    }

    PostOrderTraverse(node->LeftChild(), function);
    PostOrderTraverse(node->RightChild(), function);
    function(node->Element());
  }

  template <typename Data> void
  BinaryTree<Data>::InOrderTraverse(Node* node, TraverseFun function) const {
    if (node == nullptr) {
      return;
    }

    InOrderTraverse(node->LeftChild(), function);
    function(node->Element());
    InOrderTraverse(node->RightChild(), function);
  }

  template <typename Data> void
  BinaryTree<Data>::BreadthTraverse(Node* node, TraverseFun function) const {
    lasd::QueueVec<Node*> queue;
    queue.Enqueue(node);
    const Node* current;

    for (ulong i = 0; !(queue.Empty()); i++) {
      current = queue.HeadNDequeue();
      function(current->Element());

      if (current->HasLeftChild()) {
        queue.Enqueue(current->LeftChild());
      }

      if (current->HasRightChild()) {
        queue.Enqueue(current->RightChild());
      }
    }
  }
}