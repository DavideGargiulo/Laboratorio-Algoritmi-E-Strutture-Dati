namespace lasd {

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newSize) {
    while (tableSize < newSize) {
      tableSize *= 2;
    }
    table.Resize(tableSize);
  }

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& container) : HashTableClsAdr(container.Size()) {
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

  template <typename Data> HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long newTableSize, MappableContainer<Data>&& container) : HashTableClsAdr(newTableSize) {
    InsertAll(std::move(container));
  }

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& hashTable) : HashTable<Data>(hashTable), table(hashTable.table) {}

  template <typename Data>
  HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& hashTable) noexcept : HashTable<Data>(std::move(hashTable)) {
    std::swap(table, hashTable.table);
  }

  template <typename Data> HashTableClsAdr<Data>&
  HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& hashTable) {
    HashTable<Data>::operator=(hashTable);
    table = hashTable.table;
    return *this;
  }

  template <typename Data> HashTableClsAdr<Data>&
  HashTableClsAdr<Data>::operator=(HashTableClsAdr&& hashTable) noexcept {
    HashTable<Data>::operator=(std::move(hashTable));
    std::swap(table, hashTable.table);
    return *this;
  }

  template <typename Data> inline bool
  HashTableClsAdr<Data>::operator==(const HashTableClsAdr& hashTable) const noexcept {
    if (size != hashTable.size) {
      return false;
    }

    bool equal = true;
    for (unsigned long i = 0; i < tableSize; ++i) {
      table[i].Traverse([&](const Data &data) { 
        equal &= hashTable.Exists(data);
      });

      if (!equal) {
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
    return table[HashKey(data)].Insert(data) && ++size;
  }

  template <typename Data> bool
  HashTableClsAdr<Data>::Insert(Data&& data) {
    return table[HashKey(data)].Insert(std::move(data)) && ++size;
  }

  template <typename Data> bool
  HashTableClsAdr<Data>::Remove(const Data& data) {
    return table[HashKey(data)].Remove(data) && size--;
  }

  template <typename Data> bool
  HashTableClsAdr<Data>::Exists(const Data& data) const noexcept {
    return table[HashKey(data)].Exists(data);
  }

  template <typename Data> void
  HashTableClsAdr<Data>::Resize(unsigned long newTableSize) {
    if (!newTableSize) {
      Clear();
      return;
    }

    if (newTableSize < 128 || newTableSize == tableSize) {
      return;
    }

    HashTableClsAdr<Data> newTable(newTableSize);
    for (unsigned long i = 0; i < tableSize; ++i) {
      newTable.InsertAll(table[i]);
    }

    std::swap(*this, newTable);
  }

  template <typename Data> void HashTableClsAdr<Data>::Clear() noexcept {
    size = 0;
    tableSize = 128;
    table.Resize(tableSize);
    for (unsigned long i = 0; i < tableSize; ++i) {
      table[i].Clear();
    }
  }
}