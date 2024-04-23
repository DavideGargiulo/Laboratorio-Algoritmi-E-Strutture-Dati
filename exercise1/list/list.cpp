namespace lasd {

  // Node constructor with an initial value.
  template <typename Data> 
  List<Data>::Node::Node(const Data& initialValue) : value{initialValue} {}


  // Node move constructor.
  template <typename Data> 
  List<Data>::Node::Node(Data&& movedValue) noexcept {
    std::swap(movedValue, value);
  }

  // Node copy constructor.
  template <typename Data>
  List<Data>::Node::Node(const Node& otherNode) : value(otherNode.value) {}

  // Node move constructor.
  template <typename Data>
  List<Data>::Node::Node(Node&& otherNode) noexcept : value(std::move(otherNode.value)), next(otherNode.next) {
    otherNode.next = nullptr;
  }

  // Node destructor.
  template <typename Data>
  List<Data>::Node::~Node() { 
    delete next;
  }

  // Equality operator for nodes.
  template <typename Data> inline bool
  List<Data>::Node::operator==(const Node& otherNode) const noexcept {
    return value == otherNode.value;
  }

  // Inequality operator for nodes.
  template <typename Data> inline bool
  List<Data>::Node::operator!=(const Node& otherNode) const noexcept {
    return value != otherNode.value;
  }

  // Constructor taking a traversable container: Initializes the list with the elements of the provided container.
  template <typename Data>
  List<Data>::List(const TraversableContainer<Data>& container) {
		container.Traverse([this](const Data& currentData) {
			InsertAtBack(currentData);
		});
  }

  // Constructor taking a mappable container: Initializes the list with the elements of the provided container.
  template <typename Data>
	List<Data>::List(MappableContainer<Data>&& container) {
		container.Map([this](Data& currentData) {
			InsertAtBack(std::move(currentData));
		});
  }

  // Copy constructor: Initializes the list as a copy of another list.
  template <typename Data>
  List<Data>::List(const List<Data>& sourceList) {
    if (!(size = sourceList.size))
      return;

    head = new Node(*(sourceList.head));
    tail = head;

    Node *currentNode = sourceList.head->next;

    while (currentNode) {
      tail->next = new Node(*currentNode);
      tail = tail->next;
      currentNode = currentNode->next;
    }
  }

  // Move constructor: Initializes the list by moving the contents of another list.
  template <typename Data>
  List<Data>::List(List<Data>&& sourceList) {
    std::swap(size, sourceList.size);
    std::swap(head, sourceList.head);
    std::swap(tail, sourceList.tail);
  }

  // List destructor.
  template <typename Data>
  List<Data>::~List() {
    Node* currentNode = head;
    while (currentNode != nullptr) {
      Node* nextNode = currentNode->next;
      currentNode->next = nullptr; 
      delete currentNode;          
      currentNode = nextNode;          
    }
    head = tail = nullptr; 
    size = 0;
  }

  // Copy assignment operator: Assigns the contents of another list to this list.
  template <typename Data> List<Data>& 
  List<Data>::operator=(const List<Data>& sourceList) {
    if (this == &sourceList) {
      return *this;
    }

    if (sourceList.head == nullptr) {
      Clear();
      return *this;
    }

    Clear();

    Node* sourceNode = sourceList.head;
    Node* lastNewNode = nullptr;

    while (sourceNode) {
      Node* newNode = new Node(sourceNode->value);
      if (lastNewNode == nullptr) {
        head = newNode;
      } else {
        lastNewNode->next = newNode;
      }
      lastNewNode = newNode;

      sourceNode = sourceNode->next;
    }

    tail = lastNewNode;
    size = sourceList.size;

    return *this;
  }

  // Move assignment operator: Assigns the contents of another list to this list by moving.
  template <typename Data>
  List<Data>& List<Data>::operator=(List<Data>&& sourceList) noexcept {
    std::swap(size, sourceList.size);
    std::swap(head, sourceList.head);
    std::swap(tail, sourceList.tail);
    return *this;
  }

  // Equality operator: Checks if two lists are equal in size and content.
  template <typename Data> inline bool
  List<Data>::operator==(const List<Data> &otherList) const noexcept {
    if (size != otherList.size)
      return false;

    Node *current = head, *otherCurrent = otherList.head;

    while (current != nullptr) {
      if (current->value != otherCurrent->value)
        return false;
      current = current->next;
      otherCurrent = otherCurrent->next;
    }
    return true;
  }

  // Inequality operator: Checks if two lists are not equal in size or content.
  template <typename Data> inline bool
  List<Data>::operator!=(const List<Data>& otherList) const noexcept {
    return !(*this == otherList);
  }

  // Access operator (const version) to retrieve element at a specific index.
  template <typename Data> inline const Data&
  List<Data>::operator[](unsigned long index) const {
		if (index >= size) {
			throw std::out_of_range("Index out of range");
		}

		Node* currentNode = head;
		for (unsigned long i = 0; i < index; ++i) {
			currentNode = currentNode->next;
		}
		return currentNode->value;
  }

  // Access operator to retrieve element at a specific index.
  template <typename Data> inline Data&
  List<Data>::operator[](unsigned long index) {
		if (index >= size)
			throw std::out_of_range("Index out of range");

		Node* currentNode = head;
		for (unsigned long i = 0; i < index; ++i) {
			currentNode = currentNode->next;
		}
		return currentNode->value;
  }

  // Insert an element at the front of the list.
  template <typename Data> void
  List<Data>::InsertAtFront(const Data& data) {
		Node* newNode = new Node(data);
		newNode->next = head;
		head = newNode;

		if (tail == nullptr) {
			tail = head;
		}

		++size;
  }

  // Move version of the InsertAtFront function.
  template <typename Data>
  void List<Data>::InsertAtFront(Data&& data) {
    Node *newNode = new Node(std::move(data));
    newNode->next = head;
    head = newNode;
    if (tail == nullptr)
      tail = head;
    ++size;
  }

  // Remove the element at the front of the list.
  template <typename Data> void
  List<Data>::RemoveFromFront() {
		if (!size) {
			throw std::length_error("List is empty");
		}

		Node* nodeToRemove = head;
    if (head == tail) {
      head = tail = nullptr;
    } else {
      head = head->next;
    }

		nodeToRemove->next = nullptr;
		delete nodeToRemove;
		--size;
  }

  // Retrieve the element at the front of the list and then remove it.
  template <typename Data> Data
  List<Data>::FrontNRemove() {
    if (!size) {
      throw std::length_error("List is empty");
    }

    Node* nodeToRemove = head;
    if (head == tail) {
      head = tail = nullptr;
    } else {
      head = head->next;
    }

    nodeToRemove->next = nullptr;
    Data data = std::move(nodeToRemove->value);
    delete nodeToRemove;
    --size;
    return data;
  }

  // Insert an element at the back of the list.
  template <typename Data> void
  List<Data>::InsertAtBack(const Data& data) {
		Node* newNode = new Node(data);

		if (size++) {
      tail->next = newNode;
    } else {
      head = newNode;
    }

    tail = newNode;
  }

  // Move version of the InsertAtBack function.
  template <typename Data> void
  List<Data>::InsertAtBack(Data&& data) {
		Node* newNode = new Node(std::move(data));

    if (size++) {
      tail->next = newNode;
    } else {
      head = newNode;
    }

    tail = newNode;
  }

  // Insert an element into the list if it does not already exist.
  template <typename Data> inline bool
  List<Data>::Insert(const Data& data) {
		if (Exists(data)) {
			return false;
		}

		InsertAtBack(data);
		return true;
  }

  // Move version of the Insert function.
  template <typename Data> inline bool
  List<Data>::Insert(Data&& data) {
		if (Exists(data)) {
			return false;
		}

		InsertAtBack(std::move(data));
		return true;
  }

  // Remove an element from the list.
  template <typename Data> inline bool
  List<Data>::Remove(const Data& data) {
		if (!size) {
			return false;
		}

		if (head->value == data) {
			RemoveFromFront();
			return true;
		}

		Node* current = head->next;
		Node* previousNode = head;

		while (current != nullptr) {
      if (current->value == data) {
        previousNode->next = current->next;
        if (current->next) {
          current->next = nullptr;
        } else {
          tail = previousNode;
        }

        delete current;
        --size;
        return true;
      }
      previousNode = current;
      current = current->next;
    }
		return false;
  }

  // Retrieve the element at the front of the list (const version).
  template <typename Data> inline const Data&
  List<Data>::Front() const {
		if (!size) {
			throw std::length_error("List is empty");
		}
		return head->value;
  }

  // Retrieve the element at the front of the list (non-const version).
  template <typename Data> inline Data&
  List<Data>::Front() {
		if (!size) {
			throw std::length_error("List is empty");
		}
		return head->value;
  }

  // Retrieve the element at the back of the list (const version).
  template <typename Data> inline const Data&
  List<Data>::Back() const {
		if (!size) {
			throw std::length_error("List is empty");
		}
		return tail->value;
  }

  // Retrieve the element at the back of the list (non-const version).
  template <typename Data> inline Data&
  List<Data>::Back() {
		if (!size) {
			throw std::length_error("List is empty");
		}
		return tail->value;
  }

  // Clear the list, making it empty.
  template <typename Data> void
  List<Data>::Clear() {
		delete head;
		head = tail = nullptr;
		size = 0;
  }

  // Traverse the list with a given function (const version).
  template <typename Data> inline void
  List<Data>::Traverse(TraverseFun function) const {
		PreOrderTraverse(function);
  }

  // Traverse the list in pre-order with a given function (const version).
  template <typename Data> inline void
  List<Data>::PreOrderTraverse(TraverseFun function) const {
		PreOrderTraverse(function, head);
  }

  // Traverse the list in post-order with a given function (const version).
  template <typename Data> inline void
  List<Data>::PostOrderTraverse(TraverseFun function) const {
		PostOrderTraverse(function, head);
  }

  // Map the list with a given function.
  template <typename Data> inline void
  List<Data>::Map(MapFun function) {
		PreOrderMap(function);
  }

  // Map the list in pre-order with a given function.
  template <typename Data> inline void 
  List<Data>::PreOrderMap(MapFun function) {
		PreOrderMap(function, head);
  }

  // Map the list in post-order with a given function.
  template <typename Data> inline void
  List<Data>::PostOrderMap(MapFun function) {
		PostOrderMap(function, head);
  }

  // Helper function for pre-order traversal of the list.
  template <typename Data> void
  List<Data>::PreOrderTraverse(TraverseFun function, Node* currentNode) const {
		if (!currentNode) {
			return;
		}

		function(currentNode->value);
		PreOrderTraverse(function, currentNode->next);
  }
  
  // Helper function for post-order traversal of the list.
  template <typename Data> void
  List<Data>::PostOrderTraverse(TraverseFun function, Node* currentNode) const {
		if (!currentNode) {
			return;
		}

		PostOrderTraverse(function, currentNode->next);
		function(currentNode->value);
  }

  // Helper function for pre-order mapping of the list.
  template <typename Data> void
  List<Data>::PreOrderMap(MapFun function, Node* currentNode) const {
		if (!currentNode) {
			return;
		}

		function(currentNode->value);
		PreOrderMap(function, currentNode->next);
  }

  // Helper function for post-order mapping of the list.
  template <typename Data>
  void List<Data>::PostOrderMap(MapFun function, Node* currentNode) const {
		if (!currentNode) {
			return;
		}

		PostOrderMap(function, currentNode->next);
		function(currentNode->value);
  }
}