namespace lasd {

	template <typename Data>
	List<Data>::Node::Node(const Data& data) : value(data) {}

	template <typename Data>
	List<Data>::Node::Node(Data&& data) noexcept : value(std::move(data)) {}

	template <typename Data>
	List<Data>::Node::Node(const Node& node) : value(node.value) {}

	template <typename Data>
	List<Data>::Node::Node(Node&& node) noexcept : value(std::move(node.value), next(node.next)) {
		node.next = nullptr;
	}

	template <typename Data>
	List<Data>::Node::~Node() {
		delete next;
	}

	template <typename Data> inline bool
	List<Data>::Node::operator==(const Node& node) const noexcept {
		return value == node.value;
	}

	template <typename Data> inline bool
	List<Data>::Node::operator!=(const Node& node) const noexcept {
		return value != node.value;
	}

	// to be checked
	template <typename Data>
	List<Data>::List(const TraversableContainer<Data>& container) {
		Node* current = head;
		container.Traverse([&current](const Data& data) {
			current->next = new Node(data);
			current = current->next;
		});
		tail = current;
	}

	// to be checked
	template <typename Data>
	List<Data>::List(MappableContainer<Data>&& container) {
		Node* current = head;
		container.Map([&current](Data& data) {
			current->next = new Node(std::move(data));
			current = current->next;
		});
		tail = current;
	}

	template <typename Data>
	List<Data>::List(const List<Data>& otherList) : size(0), head(nullptr), tail(nullptr) {
		try {
			head = new Node(*(otherList.head));
			tail = head;
			size = 1;

			Node* tmp = otherList.head->next;
			while (tmp) {
				tail->next = new Node(*tmp);
				tail = tail->next;
				tmp = tmp->next;
				size++;
			}
		} catch (...) {
			while (head) {
				Node* tmp = head;
				head = head->next;
				delete tmp;
			}
			throw;
		}
	}

	template <typename Data>
	List<Data>::List(List<Data>&& liotherListst) noexcept {
		std::swap(size, otherList.size);
		std::swap(head, otherList.head);
		std::swap(tail, otherList.tail);
	}

	template <typename Data>
	List<Data>::~List() {
		Node* current = head;
		while (current) {
			Node* next = current->next;
			delete current;
			current = next;
		}
		head = tail = nullptr;
		size = 0;
	}

	template <typename Data> List<Data>& 
	List<Data>::operator=(const List<Data> &otherList) {
		if (this == &otherList) {
			return *this; // Handle self-assignment
		}

		List<Data> temp(otherList); // Use copy constructor to handle all copying
		std::swap(*this, temp); // Swap the current object with the temporary
		return *this;
	}

	template <typename Data> inline bool
	List<Data>::operator==(const List<Data>& otherList) const noexcept {
		if (this->size != otherList.size) {
			return false;
		}

		Node* currentNode = head;
		Node* otherNode = otherList.head;

		while (currentNode) {
			if (currentNode->value != otherNode->value) {
				return false;
			}
			currentNode = currentNode->next;
			otherNode = otherNode->next;
		}
		return true;
	}

	template <typename Data> inline bool
	List<Data>::operator!=(const List<Data> &otherList) const noexcept {
		return !(*this == otherList);
	}

	template <typename Data> inline const Data&
	List<Data>::operator[](unsigned long index) const {
		if (index >= size) {
			throw std::out_of_range("Index out of range");
		}

		Node* currentNode = head;
		for (unsigned long i = 0; i < index; i++) {
			currentNode = currentNode->next;
		}
		return currentNode->value;
	}

	template <typename Data> inline Data&
	List<Data>::operator[](unsigned long index) {
		if (index >= size)
			throw std::out_of_range("Index out of range");

		Node* currentNode = head;
		for (unsigned long i = 0; i < index; i++) {
			currentNode = currentNode->next;
		}
		return currentNode->value;
	}

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

	template <typename Data> void
	List<Data>::InsertAtFront(Data&& data) {
		Node* newNode = new Node(data);
		newNode->next = head;
		head = newNode;

		if (tail == nullptr) {
			tail = head;
		}

		++size;
	}

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

	template <typename Data> Data
	List<Data>::FrontNRemove() {
		if (!size) {
			throw std::length_error("List is empty");
		}

		Node* nodeToRemove = head;
		Data frontData = std::move(nodeToRemove->value);

		if (head == tail) {
			head = tail = nullptr;
		} else {
			head = head->next;
		}

		delete nodeToRemove;
		--size;
		return frontData;
	}

	template <typename Data> void
	List<Data>::InsertAtBack(const Data& data) {
		Node* newNode = new Node(data);

		if (!head) {
			head = tail = newNode;
		} else {
			tail->next = newNode;
			tail = newNode;
		}
		++size;
	}

	template <typename Data> void
	List<Data>::InsertAtBack(Data&& data) {
		Node* newNode = new Node(data);

		if (!head) {
			head = tail = newNode;
		} else {
			tail->next = newNode;
			tail = newNode;
		}
		++size;
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

		InsertAtBack(data);
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

		Node* current = head;
		Node* previousNode = head;

		while (current) {
			if (current->value == data) {
				if (current == tail) {
					tail = previousNode;
				}
				previousNode->next = current->next;
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
}