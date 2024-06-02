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
      using HashTable<Data>::InsertSome;
      using HashTable<Data>::HashKey;

      Vector<Data> table;
      Vector<int> state;

    public:
      // Default constructor
      HashTableOpnAdr();

      // Specific constructors
      HashTableOpnAdr(const unsigned long);
      HashTableOpnAdr(const TraversableContainer<Data>&);
      HashTableOpnAdr(const unsigned long, const TraversableContainer<Data>&);
      HashTableOpnAdr(MappableContainer<Data>&&) noexcept;
      HashTableOpnAdr(const unsigned long, MappableContainer<Data>&&) noexcept;

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
      // virtual unsigned long Find(const Data&, unsigned long) const noexcept;
      // virtual unsigned long FindEmpty(const Data&, unsigned long) const noexcept;
  };
}

#include "htopnadr.cpp"

#endif