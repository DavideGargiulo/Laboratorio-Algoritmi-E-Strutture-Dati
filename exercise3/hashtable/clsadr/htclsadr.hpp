#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

#include "../hashtable.hpp"
#include "../../bst/bst.hpp"

namespace lasd {

  template <typename Data>
  class HashTableClsAdr : virtual public HashTable<Data> {

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
      using HashTable<Data>::HashKey;

    public:
      // Default constructor
      HashTableClsAdr();

      // Specific constructors
      HashTableClsAdr(unsigned long); // A hash table of a given size
      HashTableClsAdr(const TraversableContainer<Data>&); // A hash table obtained from a TraversableContainer
      HashTableClsAdr(const unsigned long, const TraversableContainer<Data>&); // A hash table of a given size obtained from a TraversableContainer
      HashTableClsAdr(MappableContainer<Data>&&); // A hash table obtained from a MappableContainer
      HashTableClsAdr(const unsigned long, MappableContainer<Data>&&); // A hash table of a given size obtained from a MappableContainer

      // Copy constructor
      HashTableClsAdr(const HashTableClsAdr&);

      // Move constructor
      HashTableClsAdr(HashTableClsAdr&&) noexcept;

      // Destructor
      virtual ~HashTableClsAdr();

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      // Specific member functions (inherited from DictionaryContainer)
      // type Insert(argument) specifiers; // Override DictionaryContainer member (Copy of the value)
      // type Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
      // type Remove(argument) specifiers; // Override DictionaryContainer member

      // Specific member functions (inherited from TestableContainer)
      // type Exists(argument) specifiers; // Override TestableContainer member

      // Specific member functions (inherited from ResizableContainer)
      // type Resize(argument) specifiers; // Resize the hashtable to a given size

      // Specific member functions (inherited from ClearableContainer)
      // type Clear() specifiers; // Override Container member

  };
}

#include "htclsadr.cpp"

#endif