#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

#include "../../list/list.hpp"
#include "../../vector/vector.hpp"
#include "../hashtable.hpp"

namespace lasd {

  template <typename Data>
  class HashTableClsAdr : virtual public HashTable<Data> {
    private:

    protected:
      using HashTable<Data>::size;
      using HashTable<Data>::hashable;
      using HashTable<Data>::hashMultiplier;
      using HashTable<Data>::hashIncrement;
      using HashTable<Data>::prime;
      using HashTable<Data>::tableSize;
      using DictionaryContainer<Data>::InsertAll;
      using HashTable<Data>::HashKey;

    public:
      Vector<List<Data>> table{tableSize};
      // Default constructor
      HashTableClsAdr() = default;

      // Specific constructors
      HashTableClsAdr(const unsigned long);
      HashTableClsAdr(const TraversableContainer<Data>&);
      HashTableClsAdr(const unsigned long, const TraversableContainer<Data>&);
      HashTableClsAdr(MappableContainer<Data>&&);
      HashTableClsAdr(const unsigned long, MappableContainer<Data>&&);

      // Copy constructor
      HashTableClsAdr(const HashTableClsAdr&);

      // Move constructor
      HashTableClsAdr(HashTableClsAdr&&) noexcept;

      // Destructor
      virtual ~HashTableClsAdr() = default;

      // Copy assignment
      HashTableClsAdr& operator=(const HashTableClsAdr&);

      // Move assignment
      HashTableClsAdr& operator=(HashTableClsAdr&&) noexcept;

      // Comparison operators
      bool operator==(const HashTableClsAdr&) const noexcept;
      bool operator!=(const HashTableClsAdr&) const noexcept;

      // Specific member functions (inherited from DictionaryContainer)
      inline bool Insert(const Data&) override;
      inline bool Insert(Data&&) override;
      inline bool Remove(const Data&) override;

      // Specific member functions (inherited from TestableContainer)
      inline bool Exists(const Data&) const noexcept override;

      // Specific member functions (inherited from ResizableContainer)
      void Resize(unsigned long) override;

      // Specific member functions (inherited from ClearableContainer)
      void Clear() noexcept override;
  };
}

#include "htclsadr.cpp"

#endif