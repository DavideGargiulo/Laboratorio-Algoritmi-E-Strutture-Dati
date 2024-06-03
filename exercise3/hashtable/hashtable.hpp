#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <random>

#include "../container/dictionary.hpp"

namespace lasd {

  template <typename Data> 
  class Hashable {
    public:
      virtual unsigned long operator()(const Data&) const noexcept = 0;
  };

  template <typename Data>
  class HashTable : virtual public ResizableContainer, virtual public DictionaryContainer<Data> {
    private:

    protected:
      using DictionaryContainer<Data>::size;

      unsigned long hashMultiplier = 1;
      unsigned long hashIncrement = 0;
      static const unsigned long prime = 999999000001;

      std::default_random_engine generator = std::default_random_engine(std::random_device{}());
      std::uniform_int_distribution<unsigned long> distribution = std::uniform_int_distribution<unsigned long>(1, prime - 1);
      std::uniform_int_distribution<unsigned long> distribution2 = std::uniform_int_distribution<unsigned long>(0, prime - 1);

      static const Hashable<Data> constexpr hashable{};

      unsigned long tableSize{128};

      HashTable();
      HashTable(const HashTable&);
      HashTable(HashTable&&) noexcept;

      // Copy assignment
      HashTable& operator=(const HashTable&);

      // Move assignment
      HashTable& operator=(HashTable&&) noexcept;

    public:
      // Destructor
      virtual ~HashTable() = default;

      // Comparison operators
      inline bool operator==(const HashTable&) const noexcept = delete;
      inline bool operator!=(const HashTable&) const noexcept = delete;

    protected:
      // Auxiliary member functions
      virtual unsigned long HashKey(const Data&) const noexcept;
      virtual unsigned long HashKey(unsigned long) const noexcept;
  };
}

#include "hashtable.cpp"

#endif