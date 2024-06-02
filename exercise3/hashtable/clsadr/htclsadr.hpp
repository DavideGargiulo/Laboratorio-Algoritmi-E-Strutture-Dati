#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
#include "../../list/list.hpp"

namespace lasd {

  template <typename Data>
  class HashTableClsAdr : virtual public HashTable<Data> {

    private:

    protected:
      using HashTable<Data>::size;
      using HashTable<Data>::hashable;
      using HashTable<Data>::tableSize;
      using HashTable<Data>::InsertAll;
      using HashTable<Data>::HashKey;

      Vector<List<Data>> table;
    public:
      // Default constructor
      HashTableClsAdr();

      // Specific constructors
      HashTableClsAdr(const unsigned long); // A hash table of a given size
      HashTableClsAdr(const TraversableContainer<Data>&); // A hash table obtained from a TraversableContainer
      HashTableClsAdr(const unsigned long, const TraversableContainer<Data>&); // A hash table of a given size obtained from a TraversableContainer
      HashTableClsAdr(MappableContainer<Data>&&); // A hash table obtained from a MappableContainer
      HashTableClsAdr(const unsigned long, MappableContainer<Data>&&); // A hash table of a given size obtained from a MappableContainer

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