#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

#include "../binarytree.hpp"

namespace lasd {

  template <typename Data>
  class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {
    private:

    protected:
      using typename BinaryTree<Data>::Node;
      using typename MutableBinaryTree<Data>::MutableNode;

      struct NodeLnk : MutableNode{
        private:

        protected:

        public:
          Data element;
          NodeLnk* leftChild{nullptr};
          NodeLnk* rightChild{nullptr};

          friend class BinaryTreeLnk<Data>;

          NodeLnk() = default;
          NodeLnk(const Data& data);
          NodeLnk(Data&& data) noexcept;

          NodeLnk(const NodeLnk& node);
          NodeLnk(NodeLnk&& node) noexcept;

          virtual ~NodeLnk();

          const Data& Element() const noexcept override;
          Data& Element() noexcept override;
          inline bool HasLeftChild() const noexcept override;
          inline bool HasRightChild() const noexcept override;
          const Node& LeftChild() const override;
          const Node& RightChild() const override;
          MutableNode& LeftChild() override;
          MutableNode& RightChild() override;
      };

      NodeLnk* root{nullptr};
      using BinaryTree<Data>::size;

    public:
      // Default constructor
      BinaryTreeLnk() = default;

      // Specific constructors
      BinaryTreeLnk(const TraversableContainer<Data> &);
      BinaryTreeLnk(MappableContainer<Data> &&);

      // Copy constructor
      BinaryTreeLnk(const BinaryTreeLnk<Data>&);

      // Move constructor
      BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;

      // Destructor
      virtual ~BinaryTreeLnk();

      // Copy assignment
      BinaryTreeLnk<Data>& operator=(const BinaryTreeLnk<Data>&);

      // Move assignment
      BinaryTreeLnk<Data>& operator=(BinaryTreeLnk<Data>&&) noexcept;

      // Comparison operators
      inline bool operator==(const BinaryTreeLnk<Data>&) const noexcept;
      inline bool operator!=(const BinaryTreeLnk<Data>&) const noexcept;

      // Specific member functions (inherited from BinaryTree)
      const Node& Root() const override;

      // Specific member function (inherited from MutableBinaryTree)
      MutableNode& Root() override;

      // Specific member function (inherited from ClearableContainer)
      void Clear() override;
  };
}

#include "binarytreelnk.cpp"

#endif