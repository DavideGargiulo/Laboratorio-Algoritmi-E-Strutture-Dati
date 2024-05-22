namespace lasd {

  // Node
  template <typename Data> inline bool
  BinaryTree<Data>::Node::operator==(const Node& node) const noexcept {
    if (Element() == node.Element()) {
      bool hasLeftChild = HasLeftChild();
      bool hasRightChild = HasRightChild();

      bool nodeHasLeftChild = node.HasLeftChild();
      bool nodeHasRightChild = node.HasRightChild();

      bool right = hasLeftChild == nodeHasLeftChild;
      bool left = hasRightChild == nodeHasRightChild;

      if (left && right) {
        if (hasLeftChild && hasRightChild) {
          return LeftChild() == node.LeftChild() && RightChild() == node.RightChild();
        } else {
          if (hasLeftChild) {
            return LeftChild() == node.LeftChild();
          } else if (hasRightChild) {
            return RightChild() == node.RightChild();
          } else {
            return true;
          }
        }
      }
    }
    return false;
  }

  template <typename Data> inline bool
  BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept {
    return !(*this == node);
  }

  template <typename Data> bool
  BinaryTree<Data>::Node::IsLeaf() const noexcept {
    return !HasLeftChild() && !HasRightChild();
  }

  // BinaryTree
  template <typename Data> inline bool
  BinaryTree<Data>::operator==(const BinaryTree<Data>& tree) const noexcept {
    if (size == tree.size) {
      if (size == 0) {
        return true;
      } else {
        return Root() == tree.Root();
      }
    }
    return false;
  }

  template <typename Data> inline bool
  BinaryTree<Data>::operator!=(const BinaryTree<Data>& tree) const noexcept {
    return !(*this == tree);
  }

  template <typename Data> inline void
  BinaryTree<Data>::PreOrderTraverse(const Node* node, TraverseFun function) const {
    if (node != nullptr) {
      function(node->Element());
      if (node->HasLeftChild()) {
        PreOrderTraverse(&(node->LeftChild()), function);
      }
      if (node->HasRightChild()) {
        PreOrderTraverse(&(node->RightChild()), function);
      }
    }
  }

  template <typename Data> inline void
  BinaryTree<Data>::PostOrderTraverse(const Node* node, TraverseFun function) const {
    if (node != nullptr) {
      if (node->HasLeftChild()) {
        PostOrderTraverse(&(node->LeftChild()), function);
      }
      if (node->HasRightChild()) {
        PostOrderTraverse(&(node->RightChild()), function);
      }
      function(node->Element());
    }
  }

  template <typename Data> inline void
  BinaryTree<Data>::InOrderTraverse(const Node* node, TraverseFun function) const {
    if (node != nullptr) {
      if (node->HasLeftChild()) {
        InOrderTraverse(&(node->LeftChild()), function);
      }
      function(node->Element());
      if (node->HasRightChild()) {
        InOrderTraverse(&(node->RightChild()), function);
      }
    }
  }

  template <typename Data> inline void
  BinaryTree<Data>::BreadthTraverse(const Node* node, TraverseFun function) const {
    if (node != nullptr) {
      QueueVec<const Node*> queue;
      queue.Enqueue(node);
      const Node* current;

      for (ulong i = 0; !(queue.Empty()); i++) {
        current = queue.HeadNDequeue();
        function(current->Element());

        if (current->HasLeftChild()) {
          queue.Enqueue(&(current->LeftChild()));
        }

        if (current->HasRightChild()) {
          queue.Enqueue(&(current->RightChild()));
        }
      }
    }
  }

  // MutableBinaryTree  
  template <typename Data> inline void
  MutableBinaryTree<Data>::PreOrderMap(MutableNode* node, MapFun function) {
    if (node != nullptr) {
      function(node->Element());
      PreOrderMap(&(node->LeftChild()), function);
      PreOrderMap(&(node->RightChild()), function);
    }
  }

  template <typename Data> inline void
  MutableBinaryTree<Data>::PostOrderMap(MutableNode* node, MapFun function) {
    if (node != nullptr) {
      PostOrderMap(&(node->LeftChild()), function);
      PostOrderMap(&(node->RightChild()), function);
      function(node->Element());
    }
  }

  template <typename Data> inline void
  MutableBinaryTree<Data>::InOrderMap(MutableNode* node, MapFun function) {
    if (node != nullptr) {
      InOrderMap(&(node->LeftChild()), function);
      function(node->Element());
      InOrderMap(&(node->RightChild()), function);
    }
  }

  template <typename Data> void
  MutableBinaryTree<Data>::BreadthMap(MutableNode* node, MapFun function) {
    if (node != nullptr) {
      QueueVec<MutableNode*> queue;
      queue.Enqueue(node);
      MutableNode* current;

      for (ulong i = 0; !(queue.Empty()); i++) {
        current = queue.HeadNDequeue();
        function(current->Element());

        if (current->HasLeftChild()) {
          queue.Enqueue(&(current->LeftChild()));
        }

        if (current->HasRightChild()) {
          queue.Enqueue(&(current->RightChild()));
        }
      }
    }
  }

  // BTPreOrderIterator
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& tree) {
    if (&tree.Root() != nullptr) {
      root = &tree.Root();
      current = root;
    }
  }

  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& iterator) {
    if (iterator.root != nullptr) {
      root = iterator.root;
      current = iterator.current;
      stack = iterator.stack;
    }
  }

  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& iterator) noexcept {
    if (iterator.root != nullptr) {
      std::swap(root, iterator.root);
      std::swap(current, iterator.current);
      std::swap(stack, iterator.stack);
    }
  }

  template <typename Data> BTPreOrderIterator<Data>&
  BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& iterator) {
    if (iterator.root != nullptr) {
      root = iterator.root;
      current = iterator.current;
      stack = iterator.stack;
    }
    return *this;
  }

  template <typename Data> BTPreOrderIterator<Data>&
  BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& iterator) noexcept {
    if (iterator.root != nullptr) {
      std::swap(root, iterator.root);
      std::swap(current, iterator.current);
      std::swap(stack, iterator.stack);
    }
    return *this;
  }

  template <typename Data> inline bool
  BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& iterator) const noexcept {
    return root == iterator.root && current == iterator.current && stack == iterator.stack;
  }

  template <typename Data> inline bool
  BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& iterator) const noexcept {
    return !(*this == iterator);
  }

  template <typename Data> const Data&
  BTPreOrderIterator<Data>::operator*() const {
    if (!Terminated()) {
      return current->Element();
    } else {
      throw std::out_of_range("Iterator out of range");
    }
  }

  template <typename Data> inline bool
  BTPreOrderIterator<Data>::Terminated() const noexcept {
    return current == nullptr;
  }

  template <typename Data> inline BTPreOrderIterator<Data>&
  BTPreOrderIterator<Data>::operator++() {
    if (Terminated()) {
      throw std::out_of_range("Iterator out of range");
    } else {
      if (current->HasRightChild()) {
        stack.Push(&(current->RightChild()));
      }
      if (current->HasLeftChild()) {
        stack.Push(&(current->LeftChild()));
      }
      if (!stack.Empty()) {
        current = stack.TopNPop();
      } else {
        current = nullptr;
      }
    }
    return *this;
  }

  template <typename Data> void
  BTPreOrderIterator<Data>::Reset() noexcept {
    current = root;
    stack.Clear();
  }

  // BTPreOrderMutableIterator
  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(MutableBinaryTree<Data>& tree) : BTPreOrderIterator<Data>(tree) {}

  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& iterator) : BTPreOrderIterator<Data>(iterator) {}

  template <typename Data>
  BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& iterator) noexcept : BTPreOrderIterator<Data>(iterator) {}

  template <typename Data> BTPreOrderMutableIterator<Data>&
  BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator<Data>& iterator) {
    BTPreOrderIterator<Data>::operator=(iterator);
    return *this;
  }

  template <typename Data> BTPreOrderMutableIterator<Data>&
  BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator<Data>&& iterator) noexcept {
    BTPreOrderIterator<Data>::operator=(iterator);
    return *this;
  }

  template <typename Data> inline bool
  BTPreOrderMutableIterator<Data>::operator==(const BTPreOrderMutableIterator<Data>& iterator) const noexcept {
    return BTPreOrderIterator<Data>::operator==(iterator);
  }

  template <typename Data> inline bool
  BTPreOrderMutableIterator<Data>::operator!=(const BTPreOrderMutableIterator<Data>& iterator) const noexcept {
    return BTPreOrderIterator<Data>::operator!=(iterator);
  }

  template <typename Data> Data&
  BTPreOrderMutableIterator<Data>::operator*() {
    if (!this->Terminated()) {
      return current->Element();
    } else {
      throw std::out_of_range("Iterator out of range");
    }
  }

  // BTPostOrderIterator
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& tree) {
    if (&tree.Root() != nullptr) {
      root = &tree.Root();
      current = root;
      getLeafMostLeft();
    }
  }

  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& iterator) {
    root = iterator.root;
    current = iterator.current;
    stack = iterator.stack;
  }

  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& iterator) noexcept {
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);
    std::swap(stack, iterator.stack);
  }

  /*template <typename Data> // ! Cambiarla, funziona però è brutta
  void BTPostOrderIterator<Data>::getLeafMostLeft() noexcept {
    if(current!=nullptr){
      while (current->HasLeftChild()) {
        stack.Push(current);
        current = &(current->LeftChild());
      }
      if (current->HasRightChild()) {
        stack.Push(current);
        current = &(current->RightChild());
        getLeafMostLeft();
      }
    }
  }*/

  template <typename Data> void
  BTPostOrderIterator<Data>::getLeafMostLeft() noexcept {
    while (current != nullptr) {
      stack.Push(current);
      if (current->HasLeftChild()) {
        current = &(current->LeftChild());
      } else if (current->HasRightChild()) {
        current = &(current->RightChild());
      } else {
        current = nullptr;
      }
    }

    if (!stack.Empty()) {
      current = stack.Top();
      stack.Pop();
    }
  }

  template <typename Data> inline bool
  BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& iterator) const noexcept {
    return root == iterator.root && current == iterator.current && stack == iterator.stack;
  }

  template <typename Data> inline bool
  BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& iterator) const noexcept {
    return !(*this == iterator);
  }

  template <typename Data> const Data&
  BTPostOrderIterator<Data>::operator*() const {
    if (!Terminated()) {
      return current->Element();
    } else {
      throw std::out_of_range("Iterator out of range");
    }
  }

  template <typename Data> inline bool
  BTPostOrderIterator<Data>::Terminated() const noexcept {
    return current == nullptr;
  }

  template <typename Data> BTPostOrderIterator<Data>&
  BTPostOrderIterator<Data>::operator++() {
    if (Terminated()) {
      throw std::out_of_range("Iterator out of range");
    }

    if (stack.Empty()) {
      current = nullptr;
    } else {
      if (stack.Top()->HasRightChild() && current != &(stack.Top()->RightChild())) {
        current = &stack.Top()->RightChild();
        getLeafMostLeft();
      } else {
        current = stack.TopNPop();
      }
    }
    return *this;
  }

  template <typename Data> void
  BTPostOrderIterator<Data>::Reset() noexcept {
    current = root;
    stack.Clear();
    getLeafMostLeft();
  }

  template <typename Data> BTPostOrderIterator<Data>&
  BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& iterator) {
    root = iterator.root;
    current = iterator.current;
    stack = iterator.stack;
    return *this;
  }

  template <typename Data> BTPostOrderIterator<Data>&
  BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& iterator) noexcept {
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);
    std::swap(stack, iterator.stack);
    return *this;
  }

  // BTPostOrderMutableIterator
  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(MutableBinaryTree<Data>& tree) : BTPostOrderIterator<Data>(tree) {}

  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data>& iterator) : BTPostOrderIterator<Data>(iterator) {}

  template <typename Data>
  BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data>&& iterator) noexcept : BTPostOrderIterator<Data>(iterator) {}

  template <typename Data> BTPostOrderMutableIterator<Data>&
  BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator<Data>& iterator) {
    BTPostOrderIterator<Data>::operator=(iterator);
    return *this;
  }

  template <typename Data> BTPostOrderMutableIterator<Data>&
  BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator<Data>&& iterator) noexcept {
    BTPostOrderIterator<Data>::operator=(iterator);
    return *this;
  }

  template <typename Data> inline bool
  BTPostOrderMutableIterator<Data>::operator==(const BTPostOrderMutableIterator<Data>& iterator) const noexcept {
    return BTPostOrderIterator<Data>::operator==(iterator);
  }

  template <typename Data> inline bool
  BTPostOrderMutableIterator<Data>::operator!=(const BTPostOrderMutableIterator<Data>& iterator) const noexcept {
    return BTPostOrderIterator<Data>::operator!=(iterator);
  }

  template <typename Data> Data&
  BTPostOrderMutableIterator<Data>::operator*() {
    if (!this->Terminated()) {
      return this->current->Element();
    } else {
      throw std::out_of_range("Iterator out of range");
    }
  }

  // BTInOrderIterator
  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& tree) {
    if (&tree.Root() != nullptr) {
      root = &tree.Root();
      current = root;
      getLeafMostNode();
    }
  }

  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& iterator) {
    root = iterator.root;
    current = iterator.current;
    stack = iterator.stack;
  }

  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& iterator) noexcept {
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);
    std::swap(stack, iterator.stack);
  }

  template <typename Data> void
  BTInOrderIterator<Data>::getLeafMostNode() noexcept {
    if (current != nullptr) {
      for (; current->HasLeftChild();) {
        stack.Push(current);
        current = &(current->LeftChild());
      }
    }
  }

  template <typename Data> inline bool
  BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& iterator) const noexcept {
    return root == iterator.root && current == iterator.current && stack == iterator.stack;
  }

  template <typename Data> inline bool
  BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& iterator) const noexcept {
    return !(*this == iterator);
  }

  template <typename Data> const Data&
  BTInOrderIterator<Data>::operator*() const {
    if (!Terminated()) {
      return current->Element();
    } else {
      throw std::out_of_range("Iterator out of range");
    }
  }

  template <typename Data> inline bool
  BTInOrderIterator<Data>::Terminated() const noexcept {
    return current == nullptr;
  }

  template <typename Data> BTInOrderIterator<Data>&
  BTInOrderIterator<Data>::operator++() {
    if (Terminated()) {
      throw std::out_of_range("Iterator Terminated!");
    }
    if (current->HasRightChild()) {
      current = &(current->RightChild());
      getLeafMostNode();
    } else {
      if (stack.Empty()) {
        current = nullptr;
      } else {
        current = stack.TopNPop();
      }
    }
    return *this;
  }

  template <typename Data> BTInOrderIterator<Data>&
  BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& iterator) {
    root = iterator.root;
    current = iterator.current;
    stack = iterator.stack;
    return *this;
  }

  template <typename Data> BTInOrderIterator<Data>&
  BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& iterator) noexcept {
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);
    std::swap(stack, iterator.stack);
    return *this;
  }
  
  template <typename Data> void
  BTInOrderIterator<Data>::Reset() noexcept {
    current = root;
    stack.Clear();
    getLeafMostNode();
  }

  // BTInOrderMutableIterator
  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(MutableBinaryTree<Data>& tree) : BTInOrderIterator<Data>(tree) {}

  template <typename Data>
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(const BTInOrderMutableIterator<Data>& iterator) : BTInOrderIterator<Data>(iterator) {}

  template <typename Data>  
  BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(BTInOrderMutableIterator<Data>&& iterator) noexcept : BTInOrderIterator<Data>(iterator) {}

  template <typename Data> BTInOrderMutableIterator<Data>&
  BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator<Data>& iterator) {
    BTInOrderIterator<Data>::operator=(iterator);
    return *this;
  }

  template <typename Data> BTInOrderMutableIterator<Data>&
  BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator<Data>&& iterator) noexcept {
    BTInOrderIterator<Data>::operator=(iterator);
    return *this;
  }

  template <typename Data> inline bool
  BTInOrderMutableIterator<Data>::operator==(const BTInOrderMutableIterator<Data>& iterator) const noexcept {
    return BTInOrderIterator<Data>::operator==(iterator);
  }

  template <typename Data> inline bool
  BTInOrderMutableIterator<Data>::operator!=(const BTInOrderMutableIterator<Data>& iterator) const noexcept {
    return BTInOrderIterator<Data>::operator!=(iterator);
  }

  template <typename Data> Data&
  BTInOrderMutableIterator<Data>::operator*() {
    if (!this->Terminated()) {
      return this->current->Element();
    } else {
      throw std::out_of_range("Iterator out of range");
    }
  }

  // BTBreadthIterator
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& tree) {
    if (!tree.Empty()) {
      root = &tree.Root();
      current = root;
      queue.Enqueue(current);
    } else {
      root = nullptr;
      current = nullptr;
    }
  }

  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& iterator) {
    root = iterator.root;
    current = iterator.current;
    queue = iterator.queue;
  }

  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& iterator) noexcept {
    std::swap(root, iterator.root);
    std::swap(current, iterator.current);
    std::swap(queue, iterator.queue);
  }

  template <typename Data> inline bool
  BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& iterator) const noexcept {
    return root == iterator.root && current == iterator.current && queue == iterator.queue;
  }

  template <typename Data> inline bool
  BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& iterator) const noexcept {
    return !(*this == iterator);
  }

  template <typename Data> const Data&
  BTBreadthIterator<Data>::operator*() const {
    if (!Terminated()) {
      return current->Element();
    } else {
      throw std::out_of_range("Iterator out of range");
    }
  }

  template <typename Data> inline bool
  BTBreadthIterator<Data>::Terminated() const noexcept {
    return current == nullptr;
  }

  template <typename Data> inline BTBreadthIterator<Data>&
  BTBreadthIterator<Data>::operator++() {
    if (Terminated()) {
      throw std::out_of_range("Iterator out of range");
    }

    current = queue.HeadNDequeue();

    if (current->HasLeftChild()) {
      queue.Enqueue(&(current->LeftChild()));
    }

    if (current->HasRightChild()) {
      queue.Enqueue(&(current->RightChild()));
    }

    if (queue.Empty()) {
      current = nullptr;
    } else {
      current = queue.Head();
    }

    return *this;
  }

  template <typename Data> void
  BTBreadthIterator<Data>::Reset() noexcept {
    current = root;
    queue.Clear();
    if (current != nullptr) {
      queue.Enqueue(current);
    }
  }


  // BTBreadthMutableIterator
  template <typename Data>
  BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(MutableBinaryTree<Data>& tree) : BTBreadthIterator<Data>(tree) {}

  template <typename Data>
  BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(const BTBreadthMutableIterator<Data>& iterator) : BTBreadthIterator<Data>(iterator) {}

  template <typename Data>
  BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(BTBreadthMutableIterator<Data>&& iterator) noexcept : BTBreadthIterator<Data>(iterator) {}

  template <typename Data> BTBreadthMutableIterator<Data>&
  BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator<Data>& iterator) {
    BTBreadthIterator<Data>::operator=(iterator);
    return *this;
  }

  template <typename Data> BTBreadthMutableIterator<Data>&
  BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator<Data>&& iterator) noexcept {
    BTBreadthIterator<Data>::operator=(iterator);
    return *this;
  }

  template <typename Data> inline bool
  BTBreadthMutableIterator<Data>::operator==(const BTBreadthMutableIterator<Data>& iterator) const noexcept {
    return BTBreadthIterator<Data>::operator==(iterator);
  }

  template <typename Data> inline bool
  BTBreadthMutableIterator<Data>::operator!=(const BTBreadthMutableIterator<Data>& iterator) const noexcept {
    return BTBreadthIterator<Data>::operator!=(iterator);
  }

  template <typename Data> Data&
  BTBreadthMutableIterator<Data>::operator*() {
    if (!this->Terminated()) {
      return this->current->Element();
    } else {
      throw std::out_of_range("Iterator out of range");
    }
  }
}