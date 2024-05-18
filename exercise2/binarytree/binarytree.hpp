#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

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
      using Container::size;

    public:

      struct Node {

        protected:
          // Comparison operators
          inline bool operator==(const Node&) const noexcept;
          inline bool operator!=(const Node&) const noexcept;

        public:
          // friend class BinaryTree<Data>;
          friend class BinaryTree<Data>;
          
          // Destructor
          virtual ~Node() = default;

          // Copy assignment
          Node& operator=(const Node&) = delete;

          // Move assignment
          Node& operator=(Node&&) noexcept = delete;

          // Specific member functions
          virtual const Data& Element() const noexcept = 0;

          virtual bool IsLeaf() const noexcept;
          virtual bool HasLeftChild() const noexcept = 0;
          virtual bool HasRightChild() const noexcept = 0;

          virtual const Node& LeftChild() const = 0;
          virtual const Node& RightChild() const = 0;
      };

      // Destructor
      virtual ~BinaryTree() = default;

      // Copy assignment
      BinaryTree& operator=(const BinaryTree&) = delete;

      // Move assignment
      BinaryTree& operator=(BinaryTree&&) noexcept = delete;

      // Comparison operators
      inline bool operator==(const BinaryTree&) const noexcept;
      inline bool operator!=(const BinaryTree&) const noexcept;

      // Specific member functions
      virtual const Node& Root() const = 0;

      // Specific member function (inherited from TraversableContainer)
      using typename TraversableContainer<Data>::TraverseFun;

      inline void Traverse (TraverseFun function) const override {
        PreOrderTraverse(&Root(), function);
      };

      // Specific member function (inherited from PreOrderTraversableContainer)
      inline void PreOrderTraverse (TraverseFun function) const override {
        PreOrderTraverse(&Root(), function);
      };

      // Specific member function (inherited from PostOrderTraversableContainer)
      inline void PostOrderTraverse (TraverseFun function) const override {
        PostOrderTraverse(&Root(), function);
      };

      // Specific member function (inherited from InOrderTraversableContainer)
      inline void InOrderTraverse (TraverseFun function) const override {
        InOrderTraverse(&Root(), function);
      };

      // Specific member function (inherited from BreadthTraversableContainer)
      inline void BreadthTraverse (TraverseFun function) const override {
        BreadthTraverse(&Root(), function);
      };

    protected:
      void PreOrderTraverse(const Node*, TraverseFun) const;
      void PostOrderTraverse(const Node*, TraverseFun) const;
      void InOrderTraverse(const Node*, TraverseFun) const;
      void BreadthTraverse(const Node*, TraverseFun) const;
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
      using Container::size;
      using typename BinaryTree<Data>::Node;

    public:

      struct MutableNode : Node {
        // Must extend Node
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

      inline void Map(MapFun function) override {
        PreOrderMap(&Root(), function);
      };

      // Specific member function (inherited from PreOrderMappableContainer)
      inline void PreOrderMap(MapFun function) override {
        PreOrderMap(&Root(), function);
      };

      // Specific member function (inherited from PostOrderMappableContainer)
      inline void PostOrderMap(MapFun function) override {
        PostOrderMap(&Root(), function);
      };

      // Specific member function (inherited from InOrderMappableContainer)
      inline void InOrderMap(MapFun function) override {
        InOrderMap(&Root(), function);
      };

      // Specific member function (inherited from BreadthMappableContainer)
      inline void BreadthMap(MapFun function) override {
        BreadthMap(&Root(), function);
      };
  protected:
    void PreOrderMap(MutableNode*, MapFun);
    void PostOrderMap(MutableNode*, MapFun);
    void InOrderMap(MutableNode*, MapFun);
    void BreadthMap(MutableNode*, MapFun);
  };

  template <typename Data>
  class BTPreOrderIterator : virtual public ForwardIterator<Data>,
                             virtual public ResettableIterator<Data> {
    private:

    protected:
      const typename BinaryTree<Data>::Node* current{nullptr};
      const typename BinaryTree<Data>::Node* root{nullptr};
      StackVec<const typename BinaryTree<Data>::Node*> stack;

    public:
      // Specific constructors
      BTPreOrderIterator(const BinaryTree<Data>& tree);

      // Copy constructor
      BTPreOrderIterator(const BTPreOrderIterator& iterator);

      // Move constructor
      BTPreOrderIterator(BTPreOrderIterator&& iterator) noexcept;

      // Destructor
      virtual ~BTPreOrderIterator() = default;

      // Copy assignment
      BTPreOrderIterator& operator=(const BTPreOrderIterator& iterator);

      // Move assignment
      BTPreOrderIterator& operator=(BTPreOrderIterator&& iterator) noexcept;

      // Comparison operators
      inline bool operator==(const BTPreOrderIterator& iterator) const noexcept;
      inline bool operator!=(const BTPreOrderIterator& iterator) const noexcept;

      // Specific member functions (inherited from Iterator)
      const Data& operator*() const override;

      inline bool Terminated() const noexcept override;

      // Specific member functions (inherited from ForwardIterator)
      BTPreOrderIterator& operator++() override;

      // Specific member functions (inherited from ResettableIterator)
      void Reset() noexcept override;
  };

  template <typename Data>
  class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
                                    virtual protected BTPreOrderIterator<Data> {
    private:

    protected:
      using BTPreOrderIterator<Data>::current;

    public:
      // Specific constructors
      BTPreOrderMutableIterator(MutableBinaryTree<Data>& tree);

      // Copy constructor
      BTPreOrderMutableIterator(const BTPreOrderMutableIterator& iterator);

      // Move constructor
      BTPreOrderMutableIterator(BTPreOrderMutableIterator&& iterator) noexcept;

      // Destructor
      virtual ~BTPreOrderMutableIterator() = default;

      // Copy assignment
      BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator& iterator);

      // Move assignment
      BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&& iterator) noexcept;

      // Comparison operators
      inline bool operator==(const BTPreOrderMutableIterator& iterator) const noexcept;
      inline bool operator!=(const BTPreOrderMutableIterator& iterator) const noexcept;

      // Specific member functions (inherited from MutableIterator)
      Data& operator*() override;
  };

  template <typename Data>
  class BTPostOrderIterator : virtual public ForwardIterator<Data>,
                              virtual public ResettableIterator<Data> {
    private:

    protected:
      const typename BinaryTree<Data>::Node* current{nullptr};
      const typename BinaryTree<Data>::Node* root{nullptr};
      StackVec<const typename BinaryTree<Data>::Node*> stack;
      void getLeafMostLeft() noexcept;

    public:
      // Specific constructors
      BTPostOrderIterator(const BinaryTree<Data>& tree);

      // Copy constructor
      BTPostOrderIterator(const BTPostOrderIterator& iterator);

      // Move constructor
      BTPostOrderIterator(BTPostOrderIterator&& iterator) noexcept;

      // Destructor
      virtual ~BTPostOrderIterator() = default;

      // Copy assignment
      BTPostOrderIterator& operator=(const BTPostOrderIterator& iterator);

      // Move assignment
      BTPostOrderIterator& operator=(BTPostOrderIterator&& iterator) noexcept;

      // Comparison operators
      inline bool operator==(const BTPostOrderIterator& iterator) const noexcept;
      inline bool operator!=(const BTPostOrderIterator& iterator) const noexcept;

      // Specific member functions (inherited from Iterator)
      const Data& operator*() const override;

      inline bool Terminated() const noexcept override;

      // Specific member functions (inherited from ForwardIterator)
      BTPostOrderIterator& operator++() override;

      // Specific member functions (inherited from ResettableIterator)
      void Reset() noexcept override;
  };

  template <typename Data>
  class BTPostOrderMutableIterator : virtual public MutableIterator<Data>, 
                                     virtual protected BTPostOrderIterator<Data> {
    private:

    protected:
      using BTPostOrderIterator<Data>::current;

    public:
      // Specific constructors
      BTPostOrderMutableIterator(MutableBinaryTree<Data>& tree);

      // Copy constructor
      BTPostOrderMutableIterator(const BTPostOrderMutableIterator& iterator);

      // Move constructor
      BTPostOrderMutableIterator(BTPostOrderMutableIterator&& iterator) noexcept;

      // Destructor
      virtual ~BTPostOrderMutableIterator() = default;

      // Copy assignment
      BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator& iterator);

      // Move assignment
      BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&& iterator) noexcept;

      // Comparison operators
      inline bool operator==(const BTPostOrderMutableIterator& iterator) const noexcept;
      inline bool operator!=(const BTPostOrderMutableIterator& iterator) const noexcept;

      // Specific member functions (inherited from MutableIterator)
      Data& operator*() override;
  };

  template <typename Data>
  class BTInOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data> {
    private:

    protected:
      const typename BinaryTree<Data>::Node* current{nullptr};
      const typename BinaryTree<Data>::Node* root{nullptr};
      StackVec<const typename BinaryTree<Data>::Node*> stack;
      void getLeafMostNode() noexcept;

    public:
      // Specific constructors
      BTInOrderIterator(const BinaryTree<Data>& tree);

      // Copy constructor
      BTInOrderIterator(const BTInOrderIterator& iterator);

      // Move constructor
      BTInOrderIterator(BTInOrderIterator&& iterator) noexcept;

      // Destructor
      virtual ~BTInOrderIterator() = default;

      // Copy assignment
      BTInOrderIterator& operator=(const BTInOrderIterator& iterator);

      // Move assignment
      BTInOrderIterator& operator=(BTInOrderIterator&& iterator) noexcept;

      // Comparison operators
      inline bool operator==(const BTInOrderIterator& iterator) const noexcept;
      inline bool operator!=(const BTInOrderIterator& iterator) const noexcept;

      // Specific member functions (inherited from Iterator)
      const Data& operator*() const override;

      inline bool Terminated() const noexcept override;

      // Specific member functions (inherited from ForwardIterator)
      BTInOrderIterator& operator++() override;

      // Specific member functions (inherited from ResettableIterator)
      void Reset() noexcept override;
  };

  template <typename Data>
  class BTInOrderMutableIterator : virtual public MutableIterator<Data>,
                                   virtual protected BTInOrderIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      BTInOrderMutableIterator(MutableBinaryTree<Data>& tree);

      // Copy constructor
      BTInOrderMutableIterator(const BTInOrderMutableIterator& iterator);

      // Move constructor
      BTInOrderMutableIterator(BTInOrderMutableIterator&& iterator) noexcept;

      // Destructor
      virtual ~BTInOrderMutableIterator() = default;

      // Copy assignment
      BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator& iterator);

      // Move assignment
      BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&& iterator) noexcept;

      // Comparison operators
      inline bool operator==(const BTInOrderMutableIterator& iterator) const noexcept;
      inline bool operator!=(const BTInOrderMutableIterator& iterator) const noexcept;

      // Specific member functions (inherited from MutableIterator)
      Data& operator*() override;
  };

  template <typename Data>
  class BTBreadthIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data> {
    private:

    protected:
      const typename BinaryTree<Data>::Node* current{nullptr};
      const typename BinaryTree<Data>::Node* root{nullptr};
      QueueVec<const typename BinaryTree<Data>::Node*> queue;

    public:
      // Specific constructors
      BTBreadthIterator(const BinaryTree<Data>& tree);

      // Copy constructor
      BTBreadthIterator(const BTBreadthIterator& iterator);

      // Move constructor
      BTBreadthIterator(BTBreadthIterator&& iterator) noexcept;

      // Destructor
      virtual ~BTBreadthIterator() = default;

      // Copy assignment
      BTBreadthIterator& operator=(const BTBreadthIterator& iterator);

      // Move assignment
      BTBreadthIterator& operator=(BTBreadthIterator&& iterator) noexcept;

      // Comparison operators
      inline bool operator==(const BTBreadthIterator& iterator) const noexcept;
      inline bool operator!=(const BTBreadthIterator& iterator) const noexcept;

      // Specific member functions (inherited from Iterator)
      const Data& operator*() const override;

      inline bool Terminated() const noexcept override;

      // Specific member functions (inherited from ForwardIterator)
      BTBreadthIterator& operator++() override;

      // Specific member functions (inherited from ResettableIterator)
      void Reset() noexcept override;
  };



  template <typename Data>
  class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
                                 virtual protected BTBreadthIterator<Data> {
    private:

    protected:

    public:
      // Specific constructors
      BTBreadthMutableIterator(MutableBinaryTree<Data>& tree);

      // Copy constructor
      BTBreadthMutableIterator(const BTBreadthMutableIterator& iterator);

      // Move constructor
      BTBreadthMutableIterator(BTBreadthMutableIterator&& iterator) noexcept;

      // Destructor
      virtual ~BTBreadthMutableIterator() = default;

      // Copy assignment
      BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator& iterator);

      // Move assignment
      BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&& iterator) noexcept;

      // Comparison operators
      inline bool operator==(const BTBreadthMutableIterator& iterator) const noexcept;
      inline bool operator!=(const BTBreadthMutableIterator& iterator) const noexcept;

      // Specific member functions (inherited from MutableIterator)
      Data& operator*() override;
  };
}

#include "binarytree.cpp"

#endif