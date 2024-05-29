namespace lasd {

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr() {
    tableSize = 128;

    hashMultiplier = 2 * (distribution(generator)) + 1;
    hashIncrement = 2 * distribution2(generator);

    table.Resize(tableSize);
    state.Resize(tableSize);

    for (unsigned long i = 0; i < tableSize; i++) {
      state[i] = 0;
    }
  }

  template <typename Data>
  inline HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize) {
    tableSize = std::pow(2, std::ceil(log2((newSize < 128) ? 128 : newSize)));
    
    hashMultiplier = 2 * (distribution(generator)) + 1;
    hashIncrement = 2 * distribution2(generator);

    table.Resize(tableSize);
    state.Resize(tableSize);

    for (unsigned long i = 0; i < tableSize; i++) {
      state[i] = 0;
    }
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& container) : HashTableOpnAdr(container.Size() * 2) {
    InsertSome(container);
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, const TraversableContainer<Data>& container) : HashTableOpnAdr(newSize) {
    InsertSome(container);
  }


  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data>&& container) noexcept : HashTableOpnAdr(container.Size() * 2) {
    InsertSome(std::move(container));
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, MappableContainer<Data>&& container) noexcept : HashTableOpnAdr(newSize) {
    InsertSome(std::move(container));
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& hashTable) {
    size = hashTable.size;
    tableSize = hashTable.tableSize;
    hashMultiplier = hashTable.hashMultiplier;
    hashIncrement = hashTable.hashIncrement;
    table = hashTable.table;
    state = hashTable.state;
  }

  template <typename Data>
  HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& hashTable) noexcept {
    std::swap(size, hashTable.size);
    std::swap(tableSize, hashTable.tableSize);
    std::swap(hashMultiplier, hashTable.hashMultiplier);
    std::swap(hashIncrement, hashTable.hashIncrement);
    std::swap(table, hashTable.table);
    std::swap(state, hashTable.state);
  }

  template <typename Data> HashTableOpnAdr<Data>&
  HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& hashTable) {
    HashTableOpnAdr<Data>* temp = new HashTableOpnAdr(hashTable);
    std::swap(*this, *temp);
    delete temp;
    return *this;
  }

  template <typename Data> HashTableOpnAdr<Data>&
  HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& hashTable) noexcept {
    std::swap(size, hashTable.size);
    std::swap(tableSize, hashTable.tableSize);
    std::swap(hashMultiplier, hashTable.hashMultiplier);
    std::swap(hashIncrement, hashTable.hashIncrement);
    std::swap(table, hashTable.table);
    std::swap(state, hashTable.state);
    return *this;
  }

  template <typename Data>
  bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& hashTable) const noexcept {
    if (size != hashTable.size || tableSize != hashTable.tableSize) {
      return false;
    }

    for (unsigned long i = 0; i < tableSize; i++) {
      if (state[i] != hashTable.state[i]) {
        return false;
      }
      if (state[i] == 1 && table[i] != hashTable.table[i]) {
        return false;
      }
    }

    return true;
  }


  template <typename Data> bool
  HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& hashTable) const noexcept {
    return !(*this == hashTable);
  }

  template <typename Data>
  bool HashTableOpnAdr<Data>::Insert(const Data& data) {
    if (Exists(data)) {
      return false;
    }
    for (unsigned long i = 0; i < tableSize; ++i) {
      unsigned long index = HashKey(data, i);
      if (state[index] != 1) {
        if (size >= tableSize * 0.75) {
          Resize(tableSize * 2);
        }
        table[index] = data;
        state[index] = 1;
        size++;
        return true;
      }
    }
    return false;
  }

  template <typename Data> bool
  HashTableOpnAdr<Data>::Insert(Data&& data) {
    if (Exists(data)) {
      return false;
    }
    for (unsigned long i = 0; i < tableSize; ++i) {
      unsigned long index = HashKey(data, i);
      if (state[index] != 1) {
        if (size >= tableSize * 0.75) {
          Resize(tableSize * 2);
        }
        table[index] = std::move(data);
        state[index] = 1;
        size++;
        return true;
      }
    }
    return false;
  }

  template <typename Data> bool
  HashTableOpnAdr<Data>::Remove(const Data& data) {
    for (unsigned long i = 0; i < tableSize; ++i) {
      unsigned long index = HashKey(data, i);
      if (state[index] == 1 && table[index] == data) {
        state[index] = 2;
        --size;
        return true;
      }
    }
    return false;
  }

  template <typename Data>
  bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
    for (unsigned long i = 0; i < tableSize; ++i) {
      unsigned long index = HashKey(data, i);
      if (state[index] == 0) return false;
      if (state[index] == 1 && table[index] == data) return true;
    }
    return false;
  }

  template <typename Data> void
  HashTableOpnAdr<Data>::Resize(unsigned long newSize) {    
    Vector<Data> oldTable = std::move(table);
    Vector<int> oldState = std::move(state);
    unsigned long oldSize = tableSize;

    tableSize = newSize;
    table.Resize(newSize);
    state.Resize(newSize);

    for (unsigned long i = 0; i < tableSize; i++) {
      state[i] = 0;
    }

    size = 0;
    for (unsigned long i = 0; i < oldSize; i++) {
      if (oldState[i] == 1) {
        Insert(oldTable[i]);
      }
    }
  }

  template <typename Data> void 
  HashTableOpnAdr<Data>::Clear() noexcept {
    tableSize = 128;
    table.Clear();
    table.Resize(tableSize);
    state.Resize(tableSize);
    
    for (unsigned long i = 0; i < tableSize; i++) {
      state[i] = 0;
    }

    size = 0;
  }

  template <typename Data> unsigned long
  HashTableOpnAdr<Data>::HashKey(const Data& data, unsigned long key) const noexcept {
    unsigned long index = hashable(data);
    return (HashTable<Data>::HashKey(index) + key) % tableSize;
  }
}