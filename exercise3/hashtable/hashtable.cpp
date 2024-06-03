#include <string>

namespace lasd {

  template <typename Data> HashTable<Data>::HashTable() {
    hashMultiplier = 2 * distribution(generator) + 1;
    hashIncrement = distribution2(generator);
  }

  template <typename Data>
  HashTable<Data>::HashTable(const HashTable& hashTable) {
    size = hashTable.size;
    hashMultiplier = hashTable.hashMultiplier;
    hashIncrement = hashTable.hashIncrement;
    tableSize = hashTable.tableSize;
  }

  template <typename Data>
  HashTable<Data>::HashTable(HashTable&& hashTable) noexcept {
    std::swap(size, hashTable.size);
    std::swap(hashMultiplier, hashTable.hashMultiplier);
    std::swap(hashIncrement, hashTable.hashIncrement);
    std::swap(tableSize, hashTable.tableSize);
  }

  template <typename Data> HashTable<Data>&
  HashTable<Data>::operator=(const HashTable& hashTable) {
    size = hashTable.size;
    hashMultiplier = hashTable.hashMultiplier;
    hashIncrement = hashTable.hashIncrement;
    tableSize = hashTable.tableSize;
    return *this;
  }

  template <typename Data> HashTable<Data>&
  HashTable<Data>::operator=(HashTable&& hashTable) noexcept {
    std::swap(size, hashTable.size);
    std::swap(hashMultiplier, hashTable.hashMultiplier);
    std::swap(hashIncrement, hashTable.hashIncrement);
    std::swap(tableSize, hashTable.tableSize);
    return *this;
  }

  template <typename Data> unsigned long
  HashTable<Data>::HashKey(const Data& data) const noexcept {
    return HashKey(hashable(data));
  }

  template <typename Data> unsigned long
  HashTable<Data>::HashKey(unsigned long key) const noexcept {
    return ((hashMultiplier * key + hashIncrement) % prime) % tableSize;
  }

  template <> 
  class Hashable<int> {
    public:
      unsigned long operator()(const int& data) const noexcept { 
        return data * data;
      }
  };

  template <> 
  class Hashable<double> {
    public:
      unsigned long operator()(const double& data) const noexcept {
        long i{static_cast<long>(std::floor(data))};
        long f{static_cast<long>(pow(2, 24) * (data - i))};

        return i * f;
      }
  };

  template <> 
  class Hashable<std::string> {
    public:
      unsigned long operator()(const std::string& data) const noexcept {
        unsigned long hash = 5381;
        for (unsigned long i = 0; i < data.length(); i++) {
          hash = (hash << 5) + data[i];
        }
        return hash;
      }
  };
}