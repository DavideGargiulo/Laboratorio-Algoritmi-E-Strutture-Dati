#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <random>

#include "../container/dictionary.hpp"

namespace lasd {

  template <typename Data>
  class Hashable {
    public:
      virtual ulong operator()(const Data&) const noexcept = 0;
  };

  template <typename Data>
  class HashTable : virtual public ResizableContainer, virtual public DictionaryContainer<Data> {
    private:

    protected:
      using DictionaryContainer<Data>::size;

      unsigned long hashMultiplier = 1;
      unsigned long hashIncrement = 0;
      static const unsigned long prime = 109345121;

      std::default_random_engine generator = std::default_random_engine(std::random_device {}());
      std::uniform_int_distribution<ulong> distribution = std::uniform_int_distribution<ulong>(1, prime - 1);
      std::uniform_int_distribution<ulong> distribution2 = std::uniform_int_distribution<ulong>(0, prime - 1);

      static const Hashable<Data> hashable;

      unsigned long tableSize = 128;


    public:
      HashTable();
      HashTable(const HashTable&);
      HashTable(HashTable&&) noexcept;
      
      // Destructor
      virtual ~HashTable() = default;

      // Copy assignment
      HashTable& operator=(const HashTable&);

      // Move assignment
      HashTable& operator=(HashTable&&) noexcept;

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