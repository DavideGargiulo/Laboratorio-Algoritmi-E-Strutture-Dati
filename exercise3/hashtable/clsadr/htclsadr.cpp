namespace lasd {

  // Default constructor
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr() {
    tableSize = 128;
    size = 0;
    table.Resize(tableSize);
  }

  // Specific constructor with size
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newSize) {
    tableSize = (newSize < 128) ? 128 : newSize;
    size = 0;
    table.Resize(tableSize);
  }

  // Specific constructor from TraversableContainer
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& container)
    : HashTableClsAdr(container.Size() * 2) {
    InsertAll(container);
  }

  // Specific constructor with size from TraversableContainer
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newTableSize, const TraversableContainer<Data>& container)
    : HashTableClsAdr(newTableSize) {
    InsertAll(container);
  }

  // Specific constructor from MappableContainer
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& container)
    : HashTableClsAdr(container.Size() * 2) {
    InsertAll(std::move(container));
  }

  // Specific constructor with size from MappableContainer
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newTableSize, MappableContainer<Data>&& container)
    : HashTableClsAdr(newTableSize) {
    InsertAll(std::move(container));
  }

  // Copy constructor
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& other) {
    tableSize = other.tableSize;
    size = other.size;
    table = other.table;
  }

  // Move constructor
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& other) noexcept {
    std::swap(tableSize, other.tableSize);
    std::swap(table, other.table);
    std::swap(size, other.size);
  }

  // Destructor
  template <typename Data>
  HashTableClsAdr<Data>::~HashTableClsAdr() {
    Clear();
  }

  // Copy assignment
  template <typename Data> HashTableClsAdr<Data>&
  HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& other) {
    table = other.table;
    tableSize = other.tableSize;
    size = other.size;
    return *this;
  }

  // Move assignment
  template <typename Data> HashTableClsAdr<Data>&
  HashTableClsAdr<Data>::operator=(HashTableClsAdr&& other) noexcept {
    if (this != &other) {
      std::swap(tableSize, other.tableSize);
      std::swap(table, other.table);
      std::swap(size, other.size);
    }
    return *this;
  }

  // Comparison operators
  template <typename Data> inline bool
  HashTableClsAdr<Data>::operator==(const HashTableClsAdr& other) const noexcept {
    if (size != other.size) {
      return false;
    }
    for (unsigned long i = 0; i < tableSize; ++i) {
      if (table[i] != other.table[i]) {
        return false;
      }
    }
    return true;
  }

  template <typename Data> inline bool
  HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& other) const noexcept {
    return !(*this == other);
  }

  template <typename Data> bool
  HashTableClsAdr<Data>::Insert(const Data& data) {
    unsigned long index = HashKey(data) % tableSize;
    if (!table[index].Exists(data)) {
      table[index].InsertAtFront(data);
      ++size;
      return true;
    }
    return false;
  }

  template <typename Data> bool
  HashTableClsAdr<Data>::Insert(Data&& data) {
    unsigned long index = HashKey(data) % tableSize;
    if (!table[index].Exists(data)) {
      table[index].InsertAtFront(std::move(data));
      ++size;
      return true;
    }
    return false;
  }

  // Remove function
  template <typename Data> bool
  HashTableClsAdr<Data>::Remove(const Data& data) {
    unsigned long index = HashKey(data) % tableSize;
    if (table[index].Remove(data)) {
      --size;
      return true;
    }
    return false;
  }

  // Exists function
  template <typename Data> bool
  HashTableClsAdr<Data>::Exists(const Data& data) const noexcept {
    unsigned long index = HashKey(data) % tableSize;
    return table[index].Exists(data);
  }

  // Resize function
  template <typename Data> void
  HashTableClsAdr<Data>::Resize(unsigned long newTableSize) {
    Vector<List<Data>> oldTable = std::move(table);
    unsigned long oldTableSize = tableSize;

    tableSize = newTableSize;
    table.Resize(tableSize);

    size = 0;

    for (unsigned long i = 0; i < oldTableSize; i++) {
      while (!oldTable[i].Empty()) {
        Data data = oldTable[i].FrontNRemove();
        unsigned long index = HashKey(data) % tableSize;
        table[index].InsertAtFront(std::move(data));
        ++size;
      }
    }
  }

  // Clear function
  template <typename Data> void
  HashTableClsAdr<Data>::Clear() noexcept {
    for (unsigned long i = 0; i < tableSize; ++i) {
      table[i].Clear();
    }
    size = 0;
  }

}
