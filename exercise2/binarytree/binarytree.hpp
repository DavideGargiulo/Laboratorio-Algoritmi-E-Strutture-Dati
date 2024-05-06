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
      using Container<Data>::size;

    public:
      struct Node {
        protected:
          // Comparison operators
          inline bool operator==(const Node&) const noexcept;
          inline bool operator!=(const Node&) const noexcept {
            return !(*this == node);
          };

        public:

          friend class BinaryTree<Data>;

          // Destructor
          virtual ~Node() = default;

          // Copy assignment
          Node& operator=(const Node&) = delete;

          // Move assignment
          Node& operator=(Node&&) noexcept = delete;

          // Specific member functions
          virtual const Data& Element() const noexcept = 0;
          virtual bool IsLeaf() const noexcept {
            return !(HasLeftChild() || HasRightChild());
          };
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
      inline bool operator==(const BinaryTree& tree) const noexcept;

      inline bool operator!=(const BinaryTree& tree) const noexcept {
        return !(*this == tree);
      };

      // Specific member functions
      virtual const Node& Root() const = 0;

      // Specific member function (inherited from TraversableContainer)
      using typename TraversableContainer<Data>::TraverseFun;
      virtual void Traverse(TraverseFun function) const {
        PreOrderTraverse(Root(), function);
      };

      // Specific member function (inherited from PreOrderTraversableContainer)
      virtual void PreOrderTraverse(TraverseFun function) const {
        PreOrderTraverse(Root(), function);
      };

      // Specific member function (inherited from PostOrderTraversableContainer)
      virtual void InOrderTraverse(TraverseFun function) const {
        InOrderTraverse(Root(), function);
      };

      // Specific member function (inherited from InOrderTraversableContainer)
      virtual void PostOrderTraverse(TraverseFun function) const {
        PostOrderTraverse(Root(), function);
      };

      // Specific member function (inherited from BreadthTraversableContainer)
      virtual void BreadthTraverse(TraverseFun function) const ;

    protected:
      virtual void PreOrderTraverse(Node* node, TraverseFun) const;
      virtual void InOrderTraverse(Node* node, TraverseFun) const;
      virtual void PostOrderTraverse(Node* node, TraverseFun) const;
      virtual void BreadthTraverse(Node* node, TraverseFun) const;
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
      BTPreOrderIterator(const BinaryTree<Data>& tree);

      // Copy constructor
      BTPreOrderIterator(const BTPreOrderIterator&);

      // Move constructor
      BTPreOrderIterator(BTPreOrderIterator&&);

      // Destructor
      virtual ~BTPreOrderIterator() = default;

      // Copy assignment
      BTPreOrderIterator& operator=(const BTPreOrderIterator&);

      // Move assignment
      BTPreOrderIterator& operator=(BTPreOrderIterator&&);

      // Comparison operators
      inline bool operator==(const BTPreOrderIterator& iterator) const noexcept;
      inline bool operator!=(const BTPreOrderIterator& iterator) const noexcept {
        return !(*this == iterator);
      };

      // Specific member functions (inherited from Iterator)
      inline Data& operator*() const override;

      inline bool Terminated() const noexcept override;

      // Specific member functions (inherited from ForwardIterator)
      inline BTPreOrderIterator& operator++() override;

      // Specific member functions (inherited from ResettableIterator)
      inline void Reset() noexcept override;
  };

  template <typename Data>
  class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
                                    virtual public BTPreOrderIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      BTPreOrderMutableIterator(const MutableBinaryTree<Data>& tree);

      // Copy constructor
      BTPreOrderMutableIterator(const BTPreOrderMutableIterator&);

      // Move constructor
      BTPostOrderMutableIterator(BTPreOrderMutableIterator&&);

      // Destructor
      virtual ~BTPreOrderMutableIterator() = default;

      // Copy assignment
      BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator&);

      // Move assignment
      BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&&);

      // Comparison operators
      inline bool operator==(const BTPreOrderMutableIterator& iterator) const noexcept;
      inline bool operator!=(const BTPreOrderMutableIterator& iterator) const noexcept {
        return !(*this == iterator);
      };

      // Specific member functions (inherited from MutableIterator)
      inline Data& operator*() const override;
  };

  template <typename Data>
  class BTPostOrderIterator : virtual public ForwardIterator<Data>,
                              virtual public ResettableIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      BTPostOrderIterator(const BinaryTree<Data>& tree);

      // Copy constructor
      BTPostOrderIterator(const BTPostOrderIterator&);

      // Move constructor
      BTPostOrderIterator(BTPostOrderIterator&&);    

      // Destructor
      virtual ~BTPostOrderIterator() = default;

      // Copy assignment
      BTPostOrderIterator& operator=(const BTPostOrderIterator&);

      // Move assignment
      BTPostOrderIterator& operator=(BTPostOrderIterator&&);

      // Comparison operators
      inline bool operator==(const BTPostOrderIterator& iterator) const noexcept;
      inline bool operator!=(const BTPostOrderIterator& iterator) const noexcept {
        return !(*this == iterator);
      };

      // Specific member functions (inherited from Iterator)
      inline Data& operator*() const override;
      inline bool Terminated() const noexcept override;

      // Specific member functions (inherited from ForwardIterator)
      inline BTPostOrderIterator& operator++() override;

      // Specific member functions (inherited from ResettableIterator)
      inline void Reset() noexcept override;
  };

  template <typename Data>
  class BTPostOrderMutableIterator : virtual public MutableIterator<Data>,
                                     virtual public BTPostOrderIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      BTPostOrderMutableIterator(const MutableBinaryTree<Data>& tree);

      // Copy constructor
      BTPostOrderMutableIterator(const BTPostOrderMutableIterator&);

      // Move constructor
      BTPostOrderMutableIterator(BTPostOrderMutableIterator&&);

      // Destructor
      virtual ~BTPostOrderMutableIterator() = default;

      // Copy assignment
      BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator&);

      // Move assignment
      BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&&);   

      // Comparison operators
      inline bool operator==(const BTPostOrderMutableIterator& iterator) const noexcept;
      inline bool operator!=(const BTPostOrderMutableIterator& iterator) const noexcept {
        return !(*this == iterator);
      };

      // Specific member functions (inherited from MutableIterator)
      inline Data& operator*() const override;
  };

  template <typename Data>
  class BTInOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      BTInOrderIterator(const BinaryTree<Data>& tree);

      // Copy constructor
      BTInOrderIterator(const BTInOrderIterator&);

      // Move constructor
      BTInOrderIterator(BTInOrderIterator&&);

      // Destructor
      virtual ~BTInOrderIterator() = default;
      
      // Copy assignment
      BTInOrderIterator& operator=(const BTInOrderIterator&);

      // Move assignment
      BTInOrderIterator& operator=(BTInOrderIterator&&);

      // Comparison operators
      inline bool operator==(const BTInOrderIterator& iterator) const noexcept;
      inline bool operator!=(const BTInOrderIterator& iterator) const noexcept {
        return !(*this == iterator);
      };

      // Specific member functions (inherited from Iterator)
      inline Data& operator*() const override;
      inline bool Terminated() const noexcept override;

      // Specific member functions (inherited from ForwardIterator)
      inline BTInOrderIterator& operator++() override;

      // Specific member functions (inherited from ResettableIterator)
      inline void Reset() noexcept override;
  };

  template <typename Data>
  class BTInOrderMutableIterator : virtual public MutableIterator<Data>,
                                   virtual public BTInOrderIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      BTInOrderMutableIterator(const MutableBinaryTree<Data>& tree);

      // Copy constructor
      BTInOrderMutableIterator(const BTInOrderMutableIterator&);

      // Move constructor
      BTInOrderMutableIterator(BTInOrderMutableIterator&&);

      // Destructor
      virtual ~BTInOrderMutableIterator() = default;

      // Copy assignment
      BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator&);

      // Move assignment
      BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&&);

      // Comparison operators
      inline bool operator==(const BTInOrderMutableIterator& iterator) const noexcept;
      inline bool operator!=(const BTInOrderMutableIterator& iterator) const noexcept {
        return !(*this == iterator);
      };

      // Specific member functions (inherited from MutableIterator)
      inline Data& operator*() const override;
  };

  template <typename Data>
  class BTBreadthIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      BTBreadthIterator(const BinaryTree<Data>& tree);

      // Copy constructor
      BTBreadthIterator(const BTBreadthIterator&);

      // Move constructor
      BTBreadthIterator(BTBreadthIterator&&);

      // Destructor
      virtual ~BTBreadthIterator() = default;

      // Copy assignment
      BTBreadthIterator& operator=(const BTBreadthIterator&);

      // Move assignment
      BTBreadthIterator& operator=(BTBreadthIterator&&);

      // Comparison operators
      inline bool operator==(const BTBreadthIterator& iterator) const noexcept;
      inline bool operator!=(const BTBreadthIterator& iterator) const noexcept {
        return !(*this == iterator);
      };

      // Specific member functions (inherited from Iterator)
      inline Data& operator*() const override;

      inline bool Terminated() const noexcept override;

      // Specific member functions (inherited from ForwardIterator)
      inline BTBreadthIterator& operator++() override;

      // Specific member functions (inherited from ResettableIterator)
      inline void Reset() noexcept override;
  };

  template <typename Data>
  class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
                                   virtual public BTBreadthIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      BTBreadthMutableIterator(const MutableBinaryTree<Data>& tree);

      // Copy constructor
      BTBreadthMutableIterator(const BTBreadthMutableIterator&);

      // Move constructor
      BTBreadthMutableIterator(BTBreadthMutableIterator&&);

      // Destructor
      virtual ~BTBreadthMutableIterator() = default;

      // Copy assignment
      BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator&);

      // Move assignment
      BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&&);

      // Comparison operators
      inline bool operator==(const BTBreadthMutableIterator& iterator) const noexcept;
      inline bool operator!=(const BTBreadthMutableIterator& iterator) const noexcept {
        return !(*this == iterator);
      };

      // Specific member functions (inherited from MutableIterator)
      inline Data& operator*() const override;
  };
}

#include "binarytree.cpp"

#endif