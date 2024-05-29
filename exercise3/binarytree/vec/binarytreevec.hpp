#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

#include "../../vector/vector.hpp"
#include "../binarytree.hpp"

namespace lasd {

  template <typename Data>
  class BinaryTreeVec : virtual public MutableBinaryTree<Data> {
    private:

    protected:
      using typename BinaryTree<Data>::Node;
      using typename MutableBinaryTree<Data>::MutableNode;

      struct NodeVec : MutableNode {

      private:
      protected:
        Data element{};
        unsigned long index{0};
        BinaryTreeVec *parent{nullptr};

      public:
        friend class BinaryTreeVec<Data>;

        NodeVec() = default;
        NodeVec(const Data &data);
        NodeVec(Data &&data) noexcept;

        NodeVec(const NodeVec &node);
        NodeVec(NodeVec &&node) noexcept;

        virtual ~NodeVec() = default;

        const Data& Element() const noexcept override;
        Data& Element() noexcept override;
        inline bool HasLeftChild() const noexcept override;
        inline bool HasRightChild() const noexcept override;
        const Node& LeftChild() const override;
        const Node& RightChild() const override;
        MutableNode& LeftChild() override;
        MutableNode& RightChild() override;
      };

      using MutableBinaryTree<Data>::size;
      Vector<NodeVec*> *tree{nullptr};

    public:
      // Default constructor
      BinaryTreeVec() = default;

      // Specific constructors
      BinaryTreeVec(const TraversableContainer<Data>&);
      BinaryTreeVec(MappableContainer<Data>&&);

      // Copy constructor
      BinaryTreeVec(const BinaryTreeVec&);

      // Move constructor
      BinaryTreeVec(BinaryTreeVec&&) noexcept;

      // Destructor
      virtual ~BinaryTreeVec();

      // Copy assignment
      BinaryTreeVec &operator=(const BinaryTreeVec&);

      // Move assignment
      BinaryTreeVec &operator=(BinaryTreeVec&&) noexcept;

      // Comparison operators
      inline bool operator==(const BinaryTreeVec<Data>&) const noexcept;
      inline bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

      // Specific member functions (inherited from BinaryTree)
      const Node& Root() const override;

      // Specific member function (inherited from MutableBinaryTree)
      MutableNode& Root() override;

      // Specific member function (inherited from ClearableContainer)
      void Clear() override;

      // Specific member function (inherited from BreadthTraversableContainer)
      using typename TraversableContainer<Data>::TraverseFun;
      void BreadthTraverse(TraverseFun) const override;

      // Specific member function (inherited from BreadthMappableContainer)
      using typename MappableContainer<Data>::MapFun;
      void BreadthMap(MapFun) override;

    protected:
      // Auxiliary functions, if necessary!
  };
}

#include "binarytreevec.cpp"

#endif