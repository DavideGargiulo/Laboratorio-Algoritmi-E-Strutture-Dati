#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <memory>

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
// #include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
// #include "../queue/lst/queuelst.hpp"

namespace lasd {

  template <typename Data>
  class BinaryTree : virtual public PreOrderTraversableContainer<Data>,
                     virtual public PostOrderTraversableContainer<Data>,
                     virtual public InOrderTraversableContainer<Data>,
                     virtual public BreadthTraversableContainer<Data> {
    private:

    protected:

    public:
      struct Node {
        protected:
          // Comparison operators
          inline bool operator==(const Node&) const noexcept = delete;
          inline bool operator!=(const Node&) const noexcept = delete;

        public:

          friend class BinaryTree<Data>;

          // Destructor
          virtual ~Node() = default;

          // Copy assignment
          Node& operator=(const Node&) = delete;

          // Move assignment
          Node& operator=(Node&&) noexcept = delete;

          // Specific member functions
          virtual const Data& Element() const = 0;
          virtual bool IsLeaf() const noexcept = 0;
          virtual bool HasLeftChild() const noexcept = 0;
          virtual bool HasRightChild() const noexcept = 0;
          virtual std::unique_ptr<Node> LeftChild() const = 0;
          virtual std::unique_ptr<Node> RightChild() const = 0;
      };

      // Destructor
      virtual ~BinaryTree() = default;

      // Copy assignment
      BinaryTree& operator=(const BinaryTree&) = delete;

      // Move assignment
      BinaryTree& operator=(BinaryTree&&) noexcept = delete;

      // Comparison operators
      inline bool operator==(const BinaryTree&) const noexcept = delete;
      inline bool operator!=(const BinaryTree&) const noexcept = delete;

      // Specific member functions

      virtual const Node& Root() const = 0;  

      // Specific member function (inherited from TraversableContainer)
      using typename TraversableContainer<Data>::TraverseFun;
      virtual void Traverse(TraverseFun function) const override {
        PreOrderTraverse(function);
      };

      // Specific member function (inherited from PreOrderTraversableContainer)
      virtual void PreOrderTraverse(TraverseFun function) const override;

      // Specific member function (inherited from PostOrderTraversableContainer)
      virtual void InOrderTraverse(TraverseFun function) const override;

      // Specific member function (inherited from InOrderTraversableContainer)
      virtual void PostOrderTraverse(TraverseFun function) const override;

      // Specific member function (inherited from BreadthTraversableContainer)
      virtual void BreadthTraverse(TraverseFun function) const override;

    protected:
      // Auxiliary functions, if necessary!
  };

  template <typename Data>
  class MutableBinaryTree : virtual public ClearableContainer,
                            virtual public BinaryTree<Data>,
                            virtual public PreOrderMappableContainer<Data>,
                            virtual public PostOrderMappableContainer<Data>,
                            virtual public InOrderMappableContainer<Data>,
                            virtual public BreadthMappableContainer<Data> {
    private:

    protected:

    public:
      struct MutableNode : virtual BinaryTree<Data>::Node {

        friend class MutableBinaryTree<Data>;

        // Destructor
        virtual ~MutableNode() = default;

        // Copy assignment
        MutableNode& operator=(const MutableNode&) = delete;

        // Move assignment
        MutableNode& operator=(MutableNode&&) noexcept = delete;

        // Specific member functions

        virtual Data& Element() noexcept = 0;

        virtual MutableNode& LeftChild() = 0;
        virtual MutableNode& RightChild() = 0;
      };

      // Destructor
      virtual ~MutableBinaryTree() = default;

      // Copy assignment
      MutableBinaryTree& operator=(const MutableBinaryTree&) = delete;

      // Move assignment
      MutableBinaryTree& operator=(MutableBinaryTree&&) noexcept = delete;

      // Specific member functions
      virtual MutableNode& Root() = 0;

      // Specific member function (inherited from MappableContainer)
      using typename MappableContainer<Data>::MapFun;

      virtual void inline Map(MapFun function) override {
        PreOrderMap(function);
      };

      // Specific member function (inherited from PreOrderMappableContainer)
      virtual void PreOrderMap(MapFun function) override;

      // Specific member function (inherited from PostOrderMappableContainer)
      virtual void PostOrderMap(MapFun function) override;

      // Specific member function (inherited from InOrderMappableContainer)
      virtual void InOrderMap(MapFun function) override;

      // Specific member function (inherited from BreadthMappableContainer)
      virtual void BreadthMap(MapFun function) override;

    protected:
      // Auxiliary functions, if necessary!
  };

  template <typename Data>
  class BTPreOrderIterator : virtual public ForwardIterator<Data>,
                             virtual public ResettableIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      // BTPreOrderIterator(argument) specifiers; // An iterator over a given binary tree

      // Copy constructor
      // BTPreOrderIterator(argument) specifiers;

      // Move constructor
      // BTPreOrderIterator(argument) specifiers;

      // Destructor
      // ~BTPreOrderIterator() specifiers;

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      // Specific member functions (inherited from Iterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)

      // type Terminated() specifiers; // (should not throw exceptions)

      // Specific member functions (inherited from ForwardIterator)

      // type operator++() specifiers; // (throw std::out_of_range when terminated)

      // Specific member functions (inherited from ResettableIterator)

      // type Reset() specifiers; // (should not throw exceptions)
  };

  template <typename Data>
  class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
                                  virtual public BTPreOrderIterator<Data>{
    private:

    protected:

    public:
      // Specific constructors
      // BTPreOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree

      // Copy constructor
      // BTPreOrderMutableIterator(argument) specifiers;

      // Move constructor
      // BTPreOrderMutableIterator(argument) specifiers;

      // Destructor
      // ~BTPreOrderMutableIterator() specifiers;

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      // Specific member functions (inherited from MutableIterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)
  };

  template <typename Data>
  class BTPostOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      // BTPostOrderIterator(argument) specifiers; // An iterator over a given binary tree

      // Copy constructor
      // BTPostOrderIterator(argument) specifiers;

      // Move constructor
      // BTPostOrderIterator(argument) specifiers;      

      // Destructor
      // ~BTPostOrderIterator() specifiers;

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      // Specific member functions (inherited from Iterator)
      // type operator*() specifiers; // (throw std::out_of_range when terminated)
      // type Terminated() specifiers; // (should not throw exceptions)

      // Specific member functions (inherited from ForwardIterator)
      // type operator++() specifiers; // (throw std::out_of_range when terminated)

      // Specific member functions (inherited from ResettableIterator)
      // type Reset() specifiers; // (should not throw exceptions)
  };

  template <typename Data>
  class BTPostOrderMutableIterator : virtual public MutableIterator<Data>,
                                    virtual public BTPostOrderIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      // BTPostOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree

      // Copy constructor
      // BTPostOrderMutableIterator(argument) specifiers;

      // Move constructor
      // BTPostOrderMutableIterator(argument) specifiers;

      // Destructor
      // ~BTPostOrderMutableIterator() specifiers;

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;      

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      // Specific member functions (inherited from MutableIterator)
      // type operator*() specifiers; // (throw std::out_of_range when terminated)
  };

  template <typename Data>
  class BTInOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      // BTInOrderIterator(argument) specifiers; // An iterator over a given binary tree

      // Copy constructor
      // BTInOrderIterator(argument) specifiers;

      // Move constructor
      // BTInOrderIterator(argument) specifiers;

      // Destructor
      // ~BTInOrderIterator() specifiers;
      
      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      // Specific member functions (inherited from Iterator)
      // type operator*() specifiers; // (throw std::out_of_range when terminated)
      // type Terminated() specifiers; // (should not throw exceptions)

      // Specific member functions (inherited from ForwardIterator)
      // type operator++() specifiers; // (throw std::out_of_range when terminated)

      // Specific member functions (inherited from ResettableIterator)
      // type Reset() specifiers; // (should not throw exceptions)
  };

  template <typename Data>
  class BTInOrderMutableIterator : virtual public MutableIterator<Data>,
                                 virtual public BTInOrderIterator<Data> {
    private:

    protected:

    public:

  // Specific constructors
  // BTInOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree

  

  // Copy constructor
  // BTInOrderMutableIterator(argument) specifiers;

  // Move constructor
  // BTInOrderMutableIterator(argument) specifiers;

  

  // Destructor
  // ~BTInOrderMutableIterator() specifiers;

  

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  

  // Specific member functions (inherited from MutableIterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)

};



template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data> {

private:

  // ...

protected:

  // ...

public:

  // Specific constructors
  // BTBreadthIterator(argument) specifiers; // An iterator over a given binary tree

  

  // Copy constructor
  // BTBreadthIterator(argument) specifiers;

  // Move constructor
  // BTBreadthIterator(argument) specifiers;

  

  // Destructor
  // ~BTBreadthIterator() specifiers;

  

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)

  // type Terminated() specifiers; // (should not throw exceptions)

  

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)

  

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)

  };

  template <typename Data>
  class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
                                   virtual public BTBreadthIterator<Data>{

    private:

      // ...

    protected:

      // ...

    public:

      // Specific constructors
      // BTBreadthMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree

      

      // Copy constructor
      // BTBreadthMutableIterator(argument) specifiers;

      // Move constructor
      // BTBreadthMutableIterator(argument) specifiers;

      

      // Destructor
      // ~BTBreadthMutableIterator() specifiers;

      

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      

      // Specific member functions (inherited from MutableIterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)

  };
}

#include "binarytree.cpp"

#endif