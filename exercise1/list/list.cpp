namespace lasd {

// Node Methods


// Constructors

// Data copy constructor
  template <typename Data> 
  List<Data>::Node::Node(const Data& data) : value{data} {}

// Data move constructor
  template <typename Data> 
  List<Data>::Node::Node(Data&& data) noexcept {
    std::swap(data, value);
  }

// Copy constructor
  template <typename Data>
  List<Data>::Node::Node(const Node& otherNode) : value(otherNode.value) {}

// Move constructor
  template <typename Data>
  List<Data>::Node::Node(Node&& node) noexcept : value(std::move(node.value)), next(node.next) {
		node.next = nullptr;
  }

// Destructor
  template <typename Data>
  List<Data>::Node::~Node() { 
    delete next;
  }

// Operators

// Comparison operators
  template <typename Data> inline bool
  List<Data>::Node::operator==(const Node& node) const noexcept {
		return value == node.value;
  }

  template <typename Data> inline bool
  List<Data>::Node::operator!=(const Node& node) const noexcept {
		return value != node.value;
  }

// List Methods


// Constructors

// Copy constructor from Different DataStructures
  template <typename Data>
  List<Data>::List(const TraversableContainer<Data>& container) {
		container.Traverse([this](const Data& currentData) {
			InsertAtBack(currentData);
		});
  }

// Move constructor from Different DataStructures
  template <typename Data>
	List<Data>::List(MappableContainer<Data>&& container) {
		container.Map([this](Data& currentData) {
			InsertAtBack(std::move(currentData));
		});
  }

	template <typename Data>
	List<Data>::List(const List<Data>& otherList) {
		if (!(size = otherList.size))
			return;

		head = new Node(*(otherList.head));
		tail = head;

		Node *temp = otherList.head->next;

		while (temp) {
			tail->next = new Node(*temp);
			tail = tail->next;
			temp = temp->next;
		}
	}

// Move constructor
  template <typename Data>
  List<Data>::List(List<Data>&& otherList) {
		std::swap(size, otherList.size);
		std::swap(head, otherList.head);
		std::swap(tail, otherList.tail);
  }

// Destructor
  template <typename Data>
	List<Data>::~List() {
		Node* current = head;
		while (current != nullptr) {
				Node* next = current->next;
				current->next = nullptr; // Clear the next pointer before deletion to be safe (although not necessary with the new Node destructor).
				delete current;          // Safely delete the current node.
				current = next;          // Move to the next node.
		}
		head = tail = nullptr; // Ensure the list is completely empty.
		size = 0;
	}

// Operators

// Copy assignment
  template <typename Data> List<Data>& 
  List<Data>::operator=(const List<Data>& otherList) {
		if (!otherList.size) {
			Clear();
			return *this;
		}

		if (!size) {
			List<Data> temp = otherList;
			std::swap(temp, *this);
			return *this;
		}

		Node *wl{otherList.head};
		tail = head;

		tail->value = wl->value;

		while (tail->next && wl->next) {
			tail = tail->next;
			wl = wl->next;

			tail->value = wl->value;
		}

		if (tail->next) {
			delete tail->next;
			tail->next = nullptr;
		} else
			for (wl = wl->next; wl; wl = wl->next) {
				InsertAtBack(wl->value);
			}
		size = otherList.size;
		return *this;
  }

// Move assignment
  template <typename Data>
  List<Data>& List<Data>::operator=(List<Data>&& otherList) noexcept {
		std::swap(size, otherList.size);
		std::swap(head, otherList.head);
		std::swap(tail, otherList.tail);
		return *this;
  }

// Comparison operators
  template <typename Data> inline bool
	List<Data>::operator==(const List<Data> &otherList) const noexcept {
		if (size != otherList.size)
			return false;

		Node *temp = head, *temp2 = otherList.head;

		while (temp != nullptr) {
			if (temp->value != temp2->value)
				return false;
			temp = temp->next;
			temp2 = temp2->next;
		}
		return true;
  }


  template <typename Data> inline bool
  List<Data>::operator!=(const List<Data>& otherList) const noexcept {
		return !(*this == otherList);
  }

// Specific Operators

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


// Specific methods

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

  template <typename Data>
  void List<Data>::InsertAtFront(Data&& data) {
    Node *newNode = new Node(std::move(data));
    newNode->next = head;
    head = newNode;
    if (tail == nullptr)
      tail = head;
    ++size;
  }

  template <typename Data> void
  List<Data>::RemoveFromFront() {
		if (!size) {
			throw std::length_error("List is empty");
		}

		Node* nodeToRemove = head;
		head == tail ? head = tail = nullptr : head = head->next;

		nodeToRemove->next = nullptr;
		delete nodeToRemove;
		--size;
  }

  template <typename Data> Data
  List<Data>::FrontNRemove() {
    if (!size) {
      throw std::length_error("List is empty");
    }

    Node* nodeToRemove = head;
    head == tail ? head = tail = nullptr : head = head->next;

    nodeToRemove->next = nullptr;
    Data data = std::move(nodeToRemove->value);
    delete nodeToRemove;
    --size;
    return data;
  }

  template <typename Data> void
  List<Data>::InsertAtBack(const Data& data) {
		Node* newNode = new Node(data);

		size++ ? tail->next = newNode : head = newNode;
    tail = newNode;
  }

  template <typename Data> void
  List<Data>::InsertAtBack(Data&& data) {
		Node* newNode = new Node(std::move(data));

    size++ ? tail->next = newNode : head = newNode;
    tail = newNode;
  }

  template <typename Data> inline bool
  List<Data>::Insert(const Data& data) {
		if (Exists(data)) {
			return false;
		}

		InsertAtBack(data);
		return true;
  }

  template <typename Data> inline bool
  List<Data>::Insert(Data&& data) {
		if (Exists(data)) {
			return false;
		}

		InsertAtBack(std::move(data));
		return true;
  }

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
        current->next ? current->next = nullptr : tail = previousNode;
        delete current;
        --size;
        return true;
      }
      previousNode = current;
      current = current->next;
    }
		return false;
  }

  template <typename Data> inline const Data&
  List<Data>::Front() const {
		if (!size) {
			throw std::length_error("List is empty");
		}
		return head->value;
  }

  template <typename Data> inline Data&
  List<Data>::Front() {
		if (!size) {
			throw std::length_error("List is empty");
		}
		return head->value;
  }

  template <typename Data> inline const Data&
  List<Data>::Back() const {
		if (!size) {
			throw std::length_error("List is empty");
		}
		return tail->value;
  }

  template <typename Data> inline Data&
  List<Data>::Back() {
		if (!size) {
			throw std::length_error("List is empty");
		}
		return tail->value;
  }

// Overrided Methods

  template <typename Data> void
  List<Data>::Clear() {
		delete head;
		head = tail = nullptr;
		size = 0;
  }

  template <typename Data> inline void
  List<Data>::Traverse(TraverseFun function) const {
		PreOrderTraverse(function);
  }

  template <typename Data> inline void
  List<Data>::PreOrderTraverse(TraverseFun function) const {
		PreOrderTraverse(function, head);
  }

  template <typename Data> inline void
  List<Data>::PostOrderTraverse(TraverseFun function) const {
		PostOrderTraverse(function, head);
  }

  template <typename Data> inline void
  List<Data>::Map(MapFun function) {
		PreOrderMap(function);
  }

  template <typename Data> inline void 
  List<Data>::PreOrderMap(MapFun function) {
		PreOrderMap(function, head);
  }

  template <typename Data> inline void
  List<Data>::PostOrderMap(MapFun function) {
		PostOrderMap(function, head);
  }

// Internal Methods
  template <typename Data> void
  List<Data>::PreOrderTraverse(TraverseFun function, Node* currentNode) const {
		if (!currentNode) {
			return;
		}

		function(currentNode->value);
		PreOrderTraverse(function, currentNode->next);
  }
  
  template <typename Data> void
  List<Data>::PostOrderTraverse(TraverseFun function, Node* currentNode) const {
		if (!currentNode) {
			return;
		}

		PostOrderTraverse(function, currentNode->next);
		function(currentNode->value);
  }

  template <typename Data> void
  List<Data>::PreOrderMap(MapFun function, Node* currentNode) const {
		if (!currentNode) {
			return;
		}

		function(currentNode->value);
		PreOrderMap(function, currentNode->next);
  }

  template <typename Data>
  void List<Data>::PostOrderMap(MapFun function, Node* currentNode) const {
		if (!currentNode) {
			return;
		}

		PostOrderMap(function, currentNode->next);
		function(currentNode->value);
  }
}