namespace lasd {

  template <typename Data> inline
  HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long newSize) {
    while (tableSize < newSize) {
      tableSize *= 2;
    }

    table.Resize(tableSize);
    state.Resize(tableSize);
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& container)
      : HashTableOpnAdr(container.Size()) {
    InsertSome(container);
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long newSize, const TraversableContainer<Data>& container) : HashTableOpnAdr(newSize) {
    InsertSome(container);
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data>&& container) noexcept : HashTableOpnAdr(container.Size()) {
    InsertSome(std::move(container));
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long newSize, MappableContainer<Data>&& container) noexcept : HashTableOpnAdr(newSize) {
    InsertSome(std::move(container));
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& hashTable) : HashTable<Data>(hashTable) {
    table = hashTable.table;
    state = hashTable.state;
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& hashTable) noexcept : HashTable<Data>(std::move(hashTable)) {
    std::swap(table, hashTable.table);
    std::swap(state, hashTable.state);
  }

  template <typename Data> HashTableOpnAdr<Data>&
  HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& hashTable) {
    HashTable<Data>::operator=(hashTable);
    table = hashTable.table;
    state = hashTable.state;
    return *this;
  }

  template <typename Data> HashTableOpnAdr<Data>&
  HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& hashTable) noexcept {
    HashTable<Data>::operator=(std::move(hashTable));
    std::swap(table, hashTable.table);
    std::swap(state, hashTable.state);
    return *this;
  }

  template <typename Data> bool
  HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& hashTable) const noexcept {
    if (size != hashTable.size) {
      return false;
    }

    for (unsigned long i = 0; i < tableSize; i++) {
      if (state[i] == 1 && !hashTable.Exists(table[i])) {
        return false;
      }
    }
    return true;
  }

  template <typename Data> bool
  HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& hashTable) const noexcept {
    return !(*this == hashTable);
  }

  template <typename Data> bool
  HashTableOpnAdr<Data>::Insert(const Data& data) {
    if (size >= tableSize * 0.75) {
      Resize(size * 2);
    }

    unsigned long index = FindEmpty(data, 0);
    unsigned long hashIndex = HashKey(data, index);

    if (state[hashIndex] == 1) {
      return false;
    }

    int temp = state[hashIndex];
    table[hashIndex] = data;
    state[hashIndex] = 1;
    size++;

    if (!temp) {
      return true;
    }

    return !Remove(data, index + 1);
  }

  template <typename Data> bool
  HashTableOpnAdr<Data>::Insert(Data&& data) {
    if (size >= tableSize * 0.75) {
      Resize(size * 2);
    }

    unsigned long index = FindEmpty(data, 0);
    unsigned long hashIndex = HashKey(data, index);

    if (state[hashIndex] == 1) {
      return false;
    }

    int temp = state[hashIndex];
    std::swap(table[hashIndex], data);
    state[hashIndex] = 1;
    size++;

    if (!temp) {
      return true;
    }

    return !Remove(data, index + 1);
  }

  template <typename Data> bool
  HashTableOpnAdr<Data>::Remove(const Data& data) {
    return Remove(data, 0);
  }

  template <typename Data> bool
  HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
    return state[HashKey(data, Find(data, 0))];
  }

  template <typename Data> void
  HashTableOpnAdr<Data>::Resize(unsigned long newSize) {
    if (!newSize) {
      Clear();
      return;
    }

    if (newSize == tableSize || newSize < 128) {
      return;
    }

    HashTableOpnAdr<Data> temp(newSize);

    for (unsigned long i = 0; i < tableSize; i++) {
      if (state[i] == 1) {
        temp.Insert(table[i]);
      }
    }

    std::swap(*this, temp);
  }

  template <typename Data> void
  HashTableOpnAdr<Data>::Clear() noexcept {
    size = 0;
    tableSize = 128;
    table.Resize(tableSize);
    state.Resize(tableSize);

    for (unsigned long i = 0; i < tableSize; i++) {
      state[i] = 0;
    }
  }

  template <typename Data> unsigned long
  HashTableOpnAdr<Data>::HashKey(const Data& data, unsigned long key) const noexcept {
    return (HashKey(data) + key) % tableSize;
  }

  template <typename Data> unsigned long
  HashTableOpnAdr<Data>::Find(const Data& data, unsigned long index) const noexcept {
    while (index < tableSize) {
      if ((state[HashKey(data, index)] == 1 && table[HashKey(data, index)] == data) || state[HashKey(data, index)] == 0) {
        return index;
      }
      index++;
    }
    return index;
  }

  template <typename Data> unsigned long 
  HashTableOpnAdr<Data>::FindEmpty(const Data& data, unsigned long index) const noexcept {
    while (index < tableSize) {
      if (state[HashKey(data, index)] != 1 || table[HashKey(data, index)] == data) {
        return index;
      }
      index++;
    }
    return index;
  }

  template <typename Data> bool
  HashTableOpnAdr<Data>::Remove(const Data& data, unsigned long i) noexcept {
    unsigned long index = Find(data, i);
    unsigned long indexPos = HashKey(data, index);

    if (!state[indexPos])
      return false;

    state[indexPos] = 2;

    if (--size < tableSize * 0.25) {
      Resize(size / 0.5);
    }

    return true;
  }
}