#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

  template <typename Data>
  class HashTableOpnAdr : virtual public HashTable<Data> {
    private:

    protected:
      using HashTable<Data>::size;
      using HashTable<Data>::hashable;
      using HashTable<Data>::tableSize;
      using HashTable<Data>::hashMultiplier;
      using HashTable<Data>::hashIncrement;
      using HashTable<Data>::prime;
      using HashTable<Data>::generator;
      using HashTable<Data>::distribution;
      using HashTable<Data>::distribution2;
      using HashTable<Data>::Insert;
      using HashTable<Data>::InsertAll;
      using HashTable<Data>::InsertSome;
      using HashTable<Data>::HashKey;

      Vector<Data> table;
      Vector<int> state;

    public:
      // Default constructor
      HashTableOpnAdr();

      // Specific constructors
      HashTableOpnAdr(const unsigned long); // A hash table of a given size
      HashTableOpnAdr(const TraversableContainer<Data>&); // A hash table obtained from a TraversableContainer
      HashTableOpnAdr(const unsigned long, const TraversableContainer<Data>&); // A hash table of a given size obtained from a TraversableContainer
      HashTableOpnAdr(MappableContainer<Data>&&) noexcept; // A hash table obtained from a MappableContainer
      HashTableOpnAdr(const unsigned long, MappableContainer<Data>&&) noexcept; // A hash table of a given size obtained from a MappableContainer

      // Copy constructor
      HashTableOpnAdr(const HashTableOpnAdr&);

      // Move constructor
      HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

      // Destructor
      virtual ~HashTableOpnAdr() = default;

      // Copy assignment
      HashTableOpnAdr& operator=(const HashTableOpnAdr&);

      // Move assignment
      HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

      // Comparison operators
      inline bool operator==(const HashTableOpnAdr&) const noexcept;
      inline bool operator!=(const HashTableOpnAdr&) const noexcept;

      // Specific member functions (inherited from DictionaryContainer)
      bool Insert(const Data&) override;
      bool Insert(Data&&) override;
      bool Remove(const Data&) override;

      // Specific member functions (inherited from TestableContainer)
      bool Exists(const Data&) const noexcept override;

      // Specific member functions (inherited from ResizableContainer)
      void Resize(unsigned long);

      // Specific member functions (inherited from ClearableContainer)
      void Clear() noexcept override;

    protected:

      // Auxiliary member functions
      virtual unsigned long HashKey(const Data&, unsigned long) const noexcept;
  };
}

#include "htopnadr.cpp"

#endif