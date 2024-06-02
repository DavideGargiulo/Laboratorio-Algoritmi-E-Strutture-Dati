namespace lasd {

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr() {
    tableSize = 128;
    size = 0;
    table.Resize(tableSize);
  }

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newSize) {
    tableSize = (newSize < 128) ? 128 : newSize;
    size = 0;
    table.Resize(tableSize);
  }

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& container) : HashTableClsAdr(container.Size() * 2) {
    InsertAll(container);
  }

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newTableSize, const TraversableContainer<Data>& container) : HashTableClsAdr(newTableSize) {
    InsertAll(container);
  }

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& container) : HashTableClsAdr(container.Size() * 2) {
    InsertAll(std::move(container));
  }

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newTableSize, MappableContainer<Data>&& container) : HashTableClsAdr(newTableSize) {
    InsertAll(std::move(container));
  }
  
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& hashTable) {
    tableSize = hashTable.tableSize;
    size = hashTable.size;
    table = hashTable.table;
  }
  
  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& hashTable) noexcept {
    std::swap(tableSize, hashTable.tableSize);
    std::swap(table, hashTable.table);
    std::swap(size, hashTable.size);
  }
  
  template <typename Data> HashTableClsAdr<Data>&
  HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& hashTable) {
    table = hashTable.table;
    tableSize = hashTable.tableSize;
    size = hashTable.size;
    return *this;
  }

  template <typename Data> HashTableClsAdr<Data>&
  HashTableClsAdr<Data>::operator=(HashTableClsAdr&& hashTable) noexcept {
    std::swap(tableSize, hashTable.tableSize);
    std::swap(table, hashTable.table);
    std::swap(size, hashTable.size);
    return *this;
  }

  template <typename Data> inline bool
  HashTableClsAdr<Data>::operator==(const HashTableClsAdr& hashTable) const noexcept {
    if (size != hashTable.size) {
      return false;
    }
    for (unsigned long i = 0; i < tableSize; ++i) {
      if (table[i] != hashTable.table[i]) {
        return false;
      }
    }
    return true;
  }

  template <typename Data> inline bool
  HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& hashTable) const noexcept {
    return !(*this == hashTable);
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

  template <typename Data> bool
  HashTableClsAdr<Data>::Remove(const Data& data) {
    unsigned long index = HashKey(data) % tableSize;
    if (table[index].Remove(data)) {
      --size;
      return true;
    }
    return false;
  }

  template <typename Data> bool
  HashTableClsAdr<Data>::Exists(const Data& data) const noexcept {
    unsigned long index = HashKey(data) % tableSize;
    return table[index].Exists(data);
  }

  
  template <typename Data> void
  HashTableClsAdr<Data>::Resize(unsigned long newTableSize) {
    if (newTableSize < 1) {
      return;
    }

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

  template <typename Data> void
  HashTableClsAdr<Data>::Clear() noexcept {
    for (unsigned long i = 0; i < tableSize; ++i) {
      table[i].Clear();
    }
    size = 0;
  }
}