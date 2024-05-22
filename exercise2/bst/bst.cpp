namespace lasd {

  template <typename Data>
  BST<Data>::BST(const LinearContainer<Data>& linearContainer) {
    linearContainer.Traverse([this](const Data& data) {
      this->Insert(data);
    });
  }

  template <typename Data>
  BST<Data>::BST(MappableContainer<Data>&& mappableContainer) {
    mappableContainer.Map([this](Data&& data) { 
      this->Insert(std::move(data));
    });
  }

  template <typename Data>
  BST<Data>::BST(const BST<Data>& binarySearchTree) : BinaryTreeLnk<Data>(binarySearchTree) {}

  template <typename Data>
  BST<Data>::BST(BST<Data>&& binarySearchTree) noexcept : BinaryTreeLnk<Data>(std::move(binarySearchTree)) {}

  template <typename Data> BST<Data>&
  BST<Data>::operator=(const BST<Data>& binarySearchTree) {
    if (this != &binarySearchTree) {
      BinaryTreeLnk<Data>::operator=(binarySearchTree);
    }
    return *this;
  }

  template <typename Data> BST<Data>&
  BST<Data>::operator=(BST<Data>&& binarySearchTree) noexcept {
    if (this != &binarySearchTree) {
      BinaryTreeLnk<Data>::operator=(std::move(binarySearchTree));
    }
    return *this;
  }
  
  template <typename Data> inline bool
  BST<Data>::operator==(const BST<Data>& binarySearchTree) const noexcept {
    if (size != binarySearchTree.size) {
      return false;
    }

    QueueVec<Data> queue;
    this->InOrderTraverse([&queue](const Data& data) {
      queue.Enqueue(data);
    });

    bool isEqual = true;

    binarySearchTree.InOrderTraverse([&queue, &isEqual](const Data& data) {
      if (queue.HeadNDequeue() != data) {
        isEqual = false;
      }
    });

    return isEqual;
  }

  template <typename Data> inline bool
  BST<Data>::operator!=(const BST<Data>& binarySearchTree) const noexcept {
    return !(*this == binarySearchTree);
  }

  template <typename Data> const Data&
  BST<Data>::Min() const {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    return FindPointerToMin(root)->Element();
  }

  template <typename Data>
  Data BST<Data>::MinNRemove() {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    NodeLnk* minNode = DetachMin(root, nullptr);
    Data minData = minNode->Element();
    size--;
    return minData;
  }

  template <typename Data> void
  BST<Data>::RemoveMin() {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    NodeLnk* minNode = DetachMin(root, nullptr);
    size--;
    delete minNode;
  }

  template <typename Data> const Data&
  BST<Data>::Max() const {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }
    
    return FindPointerToMax(root)->Element();
  }

  template <typename Data> Data
  BST<Data>::MaxNRemove() {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    NodeLnk* maxNode = DetachMax(root, nullptr);
    Data maxData = maxNode->Element();
    delete maxNode;
    size--;
    return maxData;
  }

  template <typename Data> void
  BST<Data>::RemoveMax() {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    NodeLnk* maxNode = DetachMax(root, nullptr);
    size--;
    delete maxNode;
  }

  template <typename Data> const Data&
  BST<Data>::Predecessor(const Data& data) const {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    const NodeLnk* predecessorNode = FindPointerToPredecessor(root, data);
    if (!predecessorNode) {
      throw std::invalid_argument("The element has no predecessor");
    }

    return predecessorNode->Element();
  }

  template <typename Data> Data
  BST<Data>::PredecessorNRemove(const Data& data) {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    NodeLnk* predecessorNode = FindPointerToPredecessor(root, data);
    if (!predecessorNode) {
      throw std::invalid_argument("The element has no predecessor");
    }
    size--;
    return DataNDelete(predecessorNode);
  }

  template <typename Data> void
  BST<Data>::RemovePredecessor(const Data& data) {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    NodeLnk* predecessorNode = FindPointerToPredecessor(root, data);
    if (!predecessorNode) {
      throw std::invalid_argument("The element has no predecessor");
    }
    size--;
    Remove(predecessorNode->Element());
  }

  template <typename Data> const Data&
  BST<Data>::Successor(const Data& data) const {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    const NodeLnk* successorNode = FindPointerToSuccessor(root, data);
    if (!successorNode) {
      throw std::invalid_argument("The element has no successor");
    }

    return successorNode->Element();
  }

  template <typename Data> Data
  BST<Data>::SuccessorNRemove(const Data& data) {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    NodeLnk* successorNode = FindPointerToSuccessor(root, data);
    if (!successorNode) {
      throw std::invalid_argument("The element has no successor");
    }
    size--;
    return DataNDelete(successorNode);
  }

  template <typename Data> void
  BST<Data>::RemoveSuccessor(const Data& data) {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    NodeLnk* successorNode = FindPointerToSuccessor(root, data);
    if (!successorNode) {
      throw std::invalid_argument("The element has no successor");
    }
    size--;
    Remove(successorNode->Element());
  }

  template <typename Data> const typename BinaryTree<Data>::Node&
  BST<Data>::Root() const {
    if (size == 0) {
      throw std::length_error("The tree is empty");
    }

    return *root;
  }

  template <typename Data>
  bool BST<Data>::Insert(const Data& data) {
    std::unique_ptr<NodeLnk> newNode = std::make_unique<NodeLnk>(data);
    return InsertElement(root, newNode.release());
  }

  template <typename Data>
  bool BST<Data>::Insert(Data&& data) {
    std::unique_ptr<NodeLnk> newNode = std::make_unique<NodeLnk>(std::move(data));
    return InsertElement(root, newNode.release());
  }


  template <typename Data>
  bool BST<Data>::InsertElement(NodeLnk*& node, NodeLnk* newNode) {
    if (node == nullptr) {
      node = newNode;
      size++;
      return true;
    } else if (node->Element() < newNode->Element()) {
      return InsertElement(node->rightChild, newNode);
    } else {
      return InsertElement(node->leftChild, newNode);
    }
  }


  template <typename Data> typename BinaryTreeLnk<Data>::NodeLnk* 
  BST<Data>::Detach(NodeLnk** current) {
    if (current == nullptr) {
      throw std::logic_error("Current is null");
    }

    NodeLnk* result = nullptr; 

    if ((*current) != nullptr) {
      if (!((*current)->HasLeftChild())) {
        result = (*current)->rightChild;
      } else if (!((*current)->HasRightChild())) {
          result = (*current)->leftChild;
      } else {
        NodeLnk* min = DetachMin((*current)->rightChild, (*current)); 
        (*current)->Element() = min->Element(); 
      }
      
      (*current)->leftChild = nullptr;
      (*current)->rightChild = nullptr;
      delete (*current);
      *current = nullptr;
    }
    return result;
  }

  template <typename Data> typename BinaryTreeLnk<Data>::NodeLnk*
  BST<Data>::DetachMin(NodeLnk* current, NodeLnk* predecessor) {
    if (current != nullptr) {
        if (current->HasLeftChild()) {
          return DetachMin(current->leftChild, current);
        } else {
          NodeLnk* minNode = current;

          if (predecessor != nullptr) {   
            if (current == (predecessor->leftChild)) {
              predecessor->leftChild = current->rightChild;
            }
            else {
              predecessor->rightChild = current->rightChild;
            }
          }
          minNode->rightChild = nullptr;
          return minNode;
        }
    } else {
      throw std::length_error ("The tree is empty");
    }
  }

  template <typename Data> typename BinaryTreeLnk<Data>::NodeLnk*
  BST<Data>::DetachMax(NodeLnk* current, NodeLnk* predecessor) {
    if (current != nullptr) {
      if (current->HasRightChild()) {
        return DetachMax (current->rightChild, current);
      } else {
          NodeLnk* maxNode = current;

          if (predecessor != nullptr) {   
            if (current == (predecessor->leftChild)) {
              predecessor->leftChild = current->leftChild;
            } else {
              predecessor->rightChild = current->leftChild;
            }
          }
          maxNode->leftChild = nullptr;
          return maxNode;
        }
    } else {
      throw std::length_error ("from DetachMax: curr is nullptr");
    }
  }

  template <typename Data> bool
  BST<Data>::Remove(const Data& data) {
    bool result = false;
    try {
      result = Remove(data, &(root));
    } catch (std::exception & e) {
      throw;
    }
    return result;     
  }

  template <typename Data> bool
  BST<Data>::Remove(const Data& data, NodeLnk** current) {
    if ((*current) != nullptr) {
      if ((*current)->Element() < data) {
        return Remove(data, &((*current)->rightChild));
      } else if ((*current)->Element() > data) {
        return Remove (data, &((*current)->leftChild));
      } else {
        try {
          *current = Detach(current);
        } catch (std::exception & exc) {
          std::cerr<<exc.what();
          return false;
        }
        return true;
      }
    } else {
      return false;
    } 
}

  template <typename Data> bool
  BST<Data>::Exists(const Data& data) const noexcept {
    return FindPointerTo(root, data) != nullptr;
  }

  template <typename Data> void
  BST<Data>::Clear() {
    BinaryTreeLnk<Data>::Clear();
  }

  template <typename Data> typename BinaryTreeLnk<Data>::NodeLnk*&
    BST<Data>::FindPointerToSuccessor(NodeLnk*& node, const Data& data) {
      if (node != nullptr) {
        if (node->Element() <= data && node->rightChild != nullptr) {
          return FindPointerToSuccessor(node->rightChild, data);
        } else if (node->Element() > data && node->leftChild != nullptr) {
          NodeLnk*& successor = FindPointerToSuccessor(node->leftChild, data);
          if (successor == nullptr) {
            return node;
          } else {
            return successor;
          }
        }
      }
      return node;
    }

  template <typename Data> const typename BinaryTreeLnk<Data>::NodeLnk*
  BST<Data>::FindPointerToSuccessor(const NodeLnk* const & node, const Data& data) const {
    if (node != nullptr) {
      if (node->Element() <= data && node->rightChild != nullptr) {
        return FindPointerToSuccessor(node->rightChild, data);
      } else if (node->Element() > data && node->leftChild != nullptr) {
        const NodeLnk* tmp = FindPointerToSuccessor(node->leftChild, data);
        if (tmp == nullptr) {
          return node;
        } else {
          return tmp;
        }
      }
    }
    return node;
  }

  template <typename Data> typename BinaryTreeLnk<Data>::NodeLnk*&
  BST<Data>::FindPointerToPredecessor(NodeLnk*& node, const Data& data) {
    if (node == nullptr) {
      return node;
    }

    if (node->Element() < data) {
      if (node->rightChild != nullptr && node->rightChild->Element() < data) {
        return FindPointerToPredecessor(node->rightChild, data);
      }
      return node;
    }

    return FindPointerToPredecessor(node->leftChild, data);
  }

  template <typename Data> const typename BinaryTreeLnk<Data>::NodeLnk*
  BST<Data>::FindPointerToPredecessor(const NodeLnk* const& node, const Data& data) const {
    if (node == nullptr) {
      return node;
    }

    if (node->Element() < data) {
      if (node->rightChild != nullptr && node->rightChild->Element() < data) {
        return FindPointerToPredecessor(node->rightChild, data);
      }
      return node;
    }

    return FindPointerToPredecessor(node->leftChild, data);
  }

  template <typename Data> typename BinaryTreeLnk<Data>::NodeLnk*&
  BST<Data>::FindPointerTo(NodeLnk*& node, const Data& data) {
    if(node->Element() == data){
      return node;
    }else if (node->Element() > data && node->HasLeftChild()) {
      return FindPointerTo(node->leftChild, data);
    }else if (node->Element() < data && node->HasRightChild()) {
      return FindPointerTo(node->rightChild, data);
    } else {
      throw std::length_error("Element is not in the tree");
    }
  }

  template <typename Data> const typename BinaryTreeLnk<Data>::NodeLnk*
  BST<Data>::FindPointerTo(const NodeLnk* const & node, const Data& data) const {
    if(node->Element() == data){
      return node;
    }else if (node->Element() > data && node->HasLeftChild()) {
      return FindPointerTo(node->leftChild, data);
    }else if (node->Element() < data && node->HasRightChild()) {
      return FindPointerTo(node->rightChild, data);
    } else {
      return nullptr;
    }
  }

  template <typename Data> Data
  BST<Data>::DataNDelete(NodeLnk* node) {
    if (node == nullptr) {
      throw std::length_error("Node cannot be null.");
    }
    Data data = node->Element();
    Remove(data);
    return data;
  }

  template <typename Data> typename BinaryTreeLnk<Data>::NodeLnk*&
  BST<Data>::FindPointerToMin(NodeLnk*& node) noexcept {
    NodeLnk*& result = node;
    NodeLnk*& tmp = node;
    if (node != nullptr) {
      tmp = FindPointerToMin(node->leftChild);
      if (tmp != nullptr) {
        result = tmp;
      }
    }
    return result;
  }

  template <typename Data> const typename BinaryTreeLnk<Data>::NodeLnk*
  BST<Data>::FindPointerToMin(const NodeLnk* const & node) const noexcept {
    const NodeLnk* result = node;
    const NodeLnk* tmp = node;
    if (node != nullptr) {
      tmp = FindPointerToMin(node->leftChild);
      if (tmp != nullptr) {
        result = tmp;
      }
    }
    return result;
  }

  template <typename Data> typename BinaryTreeLnk<Data>::NodeLnk*&
  BST<Data>::FindPointerToMax(NodeLnk*& node) noexcept {
    NodeLnk*& result = node;
    NodeLnk*& tmp = node;
    if (node != nullptr) {
      tmp = FindPointerToMax(node->rightChild);
      if (tmp != nullptr) {
        result = tmp;
      }
    }
    return result;
  }

  template <typename Data> const typename BinaryTreeLnk<Data>::NodeLnk*
  BST<Data>::FindPointerToMax(const NodeLnk* const & node) const noexcept {
    const NodeLnk* result = node;
    const NodeLnk* tmp = node;
    if (node != nullptr) {
      tmp = FindPointerToMax(node->rightChild);
      if (tmp != nullptr) {
        result = tmp;
      }
    }
    return result;
  }
}