namespace lasd {

  // NodeLnk
  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& data) {
    element = data;
    leftChild = nullptr;
    rightChild = nullptr;
  }

  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& data) noexcept {
    std::swap(element, data);
    leftChild = nullptr;
    rightChild = nullptr;
  }

  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& node) {
    element = node.element;
    leftChild = node.leftChild;
    rightChild = node.rightChild;
  }

  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& node) noexcept {
    std::swap(element, node.element);
    std::swap(leftChild, node.leftChild);
    std::swap(rightChild, node.rightChild);
  }

  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    if (leftChild != nullptr) {
      delete leftChild;
    }
    if (rightChild != nullptr) {
      delete rightChild;
    }
  }

  template <typename Data> const Data&
  BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return element;
  }

  template <typename Data> Data&
  BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return element;
  }

  template <typename Data> inline bool
  BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return leftChild != nullptr;
  }

  template <typename Data> inline bool
  BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    return rightChild != nullptr;
  }

  template <typename Data> const typename BinaryTreeLnk<Data>::Node&
  BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    if (!HasLeftChild()) {
      throw std::out_of_range("No left child");
    }
    return *leftChild;
  }

  template <typename Data> const typename BinaryTreeLnk<Data>::Node&
  BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    if (!HasRightChild()) {
      throw std::out_of_range("No right child");
    }
    return *rightChild;
  }

  template <typename Data> typename BinaryTreeLnk<Data>::MutableNode&
  BinaryTreeLnk<Data>::NodeLnk::LeftChild() {
    if (!HasLeftChild()) {
      throw std::out_of_range("No left child");
    }
    return *leftChild;
  }

  template <typename Data> typename BinaryTreeLnk<Data>::MutableNode&
  BinaryTreeLnk<Data>::NodeLnk::RightChild() {
    if (!HasRightChild()) {
      throw std::out_of_range("No right child");
    }
    return *rightChild;
  }

  // BinaryTreeLnk
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& container) {
    size = container.Size();

    if (size == 0) {
      return;
    }

    QueueVec<NodeLnk **> queue;
    queue.Enqueue(&root);

    container.Traverse([&queue](const Data &data) {
      NodeLnk **currentNode = queue.HeadNDequeue();
      *currentNode = new NodeLnk(data);
      queue.Enqueue(&((*currentNode)->leftChild));
      queue.Enqueue(&((*currentNode)->rightChild));
    });
  }

  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data>&& container) {
    size = container.Size();

    if (size == 0) {
      return;
    }

    QueueVec<NodeLnk **> queue;
    queue.Enqueue(&root);

    container.Map([&queue](Data &data) {
      NodeLnk **currentNode = queue.HeadNDequeue();
      *currentNode = new NodeLnk(std::move(data));
      queue.Enqueue(&((*currentNode)->leftChild));
      queue.Enqueue(&((*currentNode)->rightChild));
    });
  }

  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& tree) {
    size = tree.size;

    if (size == 0) {
      return;
    }

    QueueVec<NodeLnk **> queue;
    queue.Enqueue(&root);

    tree.BreadthTraverse([&queue](const NodeLnk& node) {
      NodeLnk **currentNode = queue.HeadNDequeue();
      *currentNode = new NodeLnk(node);
      queue.Enqueue(&((*currentNode)->leftChild));
      queue.Enqueue(&((*currentNode)->rightChild));
    });
  }

  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& tree) noexcept {
    std::swap(size, tree.size);
    std::swap(root, tree.root);
  }

  template <typename Data> BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    if (root != nullptr) {
      delete root;
    }
  }

  template <typename Data> BinaryTreeLnk<Data>&
  BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& tree) {
    BinaryTreeLnk<Data> copy(tree);
    std::swap(size, copy.size);
    std::swap(root, copy.root);
    return *this;
  }

  template <typename Data> BinaryTreeLnk<Data>&
  BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& tree) noexcept {
    std::swap(size, tree.size);
    std::swap(root, tree.root);
    return *this;
  }

  template <typename Data> inline bool
  BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& tree) const noexcept {
    return MutableBinaryTree<Data>::operator==(tree);
  }

  template <typename Data> inline bool
  BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& tree) const noexcept {
    return MutableBinaryTree<Data>::operator!=(tree);
  }

  template <typename Data> const typename BinaryTreeLnk<Data>::Node&
  BinaryTreeLnk<Data>::Root() const {
    if (size == 0) {
      throw std::length_error("Empty tree");
    }
    return *root;
  }

  template <typename Data> typename BinaryTreeLnk<Data>::MutableNode&
  BinaryTreeLnk<Data>::Root() {
    if (size == 0) {
      throw std::length_error("Empty tree");
    }
    return *root;
  }

  template <typename Data> void
  BinaryTreeLnk<Data>::Clear() {
    delete root;
    root = nullptr;
    size = 0;
  }
}