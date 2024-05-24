#ifndef BST_HPP
#define BST_HPP

#include "../binarytree/lnk/binarytreelnk.hpp"

namespace lasd {

  template <typename Data>
  class BST : virtual public ClearableContainer, 
              virtual public DictionaryContainer<Data>, 
              virtual public BinaryTree<Data>, 
              virtual public BinaryTreeLnk<Data> {
    private:

    protected:
      using typename BinaryTreeLnk<Data>::NodeLnk;
      using BinaryTreeLnk<Data>::root;
      using BinaryTreeLnk<Data>::size;

    public:
      // Default constructor
      BST() = default;

      // Specific constructors
      BST(const LinearContainer<Data>&);
      BST(MappableContainer<Data>&&);

      // Copy constructor
      BST(const BST<Data>&);

      // Move constructor
      BST(BST<Data>&&) noexcept;

      // Destructor
      virtual ~BST() = default;

      // Copy assignment
      BST& operator=(const BST<Data>&);

      // Move assignment
      BST& operator=(BST<Data>&&) noexcept;

      // Comparison operators
      inline bool operator==(const BST<Data>&) const noexcept;
      inline bool operator!=(const BST<Data>&) const noexcept;

      // Specific member functions
      virtual const Data& Min() const;
      virtual Data MinNRemove();
      virtual void RemoveMin();

      virtual const Data& Max() const;
      virtual Data MaxNRemove();
      virtual void RemoveMax();

      virtual const Data& Predecessor(const Data&) const;
      virtual Data PredecessorNRemove(const Data&);
      virtual void RemovePredecessor(const Data&);

      virtual const Data& Successor(const Data&) const;
      virtual Data SuccessorNRemove(const Data&);
      virtual void RemoveSuccessor(const Data&);

      // Specific member function (inherited from BinaryTree)
      const typename BinaryTree<Data>::Node& Root() const override;

      // Specific member functions (inherited from DictionaryContainer)
      bool Insert(const Data&) override;
      bool Insert(Data&&) override;
      bool Remove(const Data&) override;

      // Specific member functions (inherited from TestableContainer)
      bool Exists(const Data&) const noexcept override;

      // Specific member function (inherited from ClearableContainer)
      void Clear() override;

    protected:
      // Auxiliary functions, if necessary!
      virtual NodeLnk* RemoveElement(NodeLnk*, const Data&);
      virtual NodeLnk* deleteRoot(NodeLnk*);
      virtual NodeLnk* DetachMin(NodeLnk*, NodeLnk*);

      bool Remove (const Data &, typename BinaryTreeLnk<Data>::NodeLnk **);
      virtual Data DataNDelete(NodeLnk*);

      virtual NodeLnk* DetachMax(NodeLnk*, NodeLnk*);

      virtual NodeLnk*& FindPointerToMin(NodeLnk*&) noexcept;
      virtual const NodeLnk* FindPointerToMin(const NodeLnk* const &) const noexcept;
      virtual NodeLnk*& FindPointerToMax(NodeLnk*&) noexcept;
      virtual const NodeLnk* FindPointerToMax(const NodeLnk* const &) const noexcept;

      virtual NodeLnk*& FindPointerTo(NodeLnk*&, const Data&);
      virtual const NodeLnk* FindPointerTo(const NodeLnk* const &, const Data&) const;

      virtual NodeLnk*& FindPointerToPredecessor(NodeLnk*&, const Data&);
      virtual const NodeLnk* FindPointerToPredecessor(const NodeLnk* const &, const Data&) const;
      virtual NodeLnk*& FindPointerToSuccessor(NodeLnk*&, const Data&);
      virtual const NodeLnk* FindPointerToSuccessor(const NodeLnk* const &, const Data&) const;

      virtual NodeLnk* InsertElement(NodeLnk*, const Data&);
  };
}

#include "bst.cpp"

#endif