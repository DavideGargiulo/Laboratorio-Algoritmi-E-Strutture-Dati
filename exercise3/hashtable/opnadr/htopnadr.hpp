#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

#include "../../vector/vector.hpp"
#include "../hashtable.hpp"

namespace lasd {

  template <typename Data>
  class HashTableOpnAdr : virtual public HashTable<Data> {
    private:

    protected:
      using HashTable<Data>::size;
      using HashTable<Data>::InsertSome;
      using HashTable<Data>::HashKey;
      using HashTable<Data>::tableSize;

      Vector<Data> table{tableSize};
      Vector<int> state{tableSize};

    public:
      // Default constructor
      HashTableOpnAdr() = default;

      // Specific constructors
      HashTableOpnAdr(const unsigned long);
      HashTableOpnAdr(const TraversableContainer<Data>&);
      HashTableOpnAdr(const unsigned long, const TraversableContainer<Data>&);
      HashTableOpnAdr(MappableContainer<Data>&&) noexcept;
      HashTableOpnAdr(const unsigned long, MappableContainer<Data>&&) noexcept;

      // Copy constructor
      HashTableOpnAdr(const HashTableOpnAdr<Data>&);

      // Move constructor
      HashTableOpnAdr(HashTableOpnAdr<Data>&&) noexcept;

      // Destructor
      virtual ~HashTableOpnAdr() = default;

      // Copy assignment
      HashTableOpnAdr& operator=(const HashTableOpnAdr<Data>&);

      // Move assignment
      HashTableOpnAdr& operator=(HashTableOpnAdr<Data>&&) noexcept;

      // Comparison operators
      inline bool operator==(const HashTableOpnAdr<Data>&) const noexcept;
      inline bool operator!=(const HashTableOpnAdr<Data>&) const noexcept;

      // Specific member functions (inherited from DictionaryContainer)
      bool Insert(const Data&) override;
      bool Insert(Data&&) override;
      bool Remove(const Data&) override;

      // Specific member functions (inherited from TestableContainer)
      virtual bool Exists(const Data&) const noexcept override;

      // Specific member functions (inherited from ResizableContainer)
      void Resize(unsigned long) override;

      // Specific member functions (inherited from ClearableContainer)
      void Clear() noexcept override;

    protected:
      // Auxiliary member functions
      unsigned long HashKey(const Data&, unsigned long) const noexcept;
      unsigned long Find(const Data&, unsigned long) const noexcept;
      unsigned long FindEmpty(const Data&, unsigned long) const noexcept;
      bool Remove(const Data&, unsigned long) noexcept;
  };
}

#include "htopnadr.cpp"

#endif