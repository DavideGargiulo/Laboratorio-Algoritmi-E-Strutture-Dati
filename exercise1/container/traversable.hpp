
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

#include <functional>
#include "testable.hpp"

namespace lasd {

  template <typename Data>
  class TraversableContainer : virtual public TestableContainer<Data> {
    private:

    protected:

    public:
      // Destructor
      virtual ~TraversableContainer() = default;

      // Copy assignment
      TraversableContainer& operator=(const TraversableContainer&) = delete;

      // Move assignment
      TraversableContainer& operator=(TraversableContainer&&) noexcept = delete;

      // Comparison operators
      bool operator==(const TraversableContainer&) const noexcept = delete;
      bool operator!=(const TraversableContainer&) const noexcept = delete;

      // Specific member function
      using TraverseFun = std::function<void(const Data &)>;

      virtual void Traverse(TraverseFun) const = 0;

      template <typename Accumulator>
      using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

      template <typename Accumulator>
      inline Accumulator Fold(FoldFun<Accumulator> function, Accumulator base) const;

      // Specific member function (inherited from TestableContainer)
      inline bool Exists(const Data&) const noexcept override;
};

  template <typename Data>
  class PreOrderTraversableContainer : virtual public TraversableContainer<Data> {
    private:

    protected:

    public:
      // Destructor
      virtual ~PreOrderTraversableContainer() = default;

      // Copy assignment
      PreOrderMappableContainer& operator=(const PreOrderMappableContainer&) = delete;

      // Move assignment
      PreOrderMappableContainer& operator=(PreOrderMappableContainer&&) noexcept = delete;

      // Comparison operators
      bool operator==(const PreOrderMappableContainer&) const noexcept = delete;
      bool operator!=(const PreOrderMappableContainer&) const noexcept = delete;

      // Specific member function
      using typename TraversableContainer<Data>::TraverseFun;

      virtual void PreOrderTraverse(const TraverseFun) const = 0;

      template <typename Accumulator>
      using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

      template <typename Accumulator>
      inline Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;

      // Specific member function (inherited from TraversableContainer)
      inline void Traverse(const TraverseFun) const override{
        PreOrderTraverse(function);
      };
  };

  template <typename Data>
  class PostOrderTraversableContainer : virtual public TraversableContainer<Data> {
    private:

    protected:

    public:
      // Destructor
      virtual ~PostOrderMappableContainer() = default;

      // Copy assignment
      PostOrderMappableContainer& operator=(const PostOrderMappableContainer&) = delete;

      // Move assignment
      PostOrderMappableContainer& operator=(PostOrderMappableContainer&&) noexcept = delete;

      // Comparison operators
      bool operator==(const PostOrderMappableContainer&) const noexcept = delete;
      bool operator!=(const PostOrderMappableContainer&) const noexcept = delete;

      // Specific member function
      using typename TraversableContainer<Data>::TraverseFun;
      virtual void PostOrderTraverse(TraverseFun) const = 0;

      template <typename Accumulator>
      using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

      template <typename Accumulator>
      inline Accumulator PostOrderFold(FoldFun<Accumulator> function, Accumulator base) const;

      // Specific member function (inherited from TraversableContainer)
      inline void Traverse(const TraverseFun) const override{
        PostOrderTraverse(function);
      };
  };

  template <typename Data>
  class InOrderTraversableContainer : virtual public TraversableContainer<Data> {
    private:

    protected:

    public:
      // Destructor
      virtual ~InOrderMappableContainer() = default;

      // Copy assignment
      InOrderMappableContainer& operator=(const InOrderMappableContainer&) = delete;

      // Move assignment
      InOrderMappableContainer& operator=(InOrderMappableContainer&&) noexcept = delete;

      // Comparison operators
      bool operator==(const InOrderMappableContainer&) const noexcept = delete;
      bool operator!=(const InOrderMappableContainer&) const noexcept = delete;

      // Specific member function
      using typename TraversableContainer<Data>::TraverseFun;

      virtual void InOrderTraverse(TraverseFun) const = 0;

      template <typename Accumulator>
      using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

      template <typename Accumulator>
      inline Accumulator InOrderFold(FoldFun<Accumulator> function, Accumulator base) const;

      // Specific member function (inherited from TraversableContainer)
      inline void Traverse(const TraverseFun) const override{
        InOrderTraverse(function);
      };
  };

  template <typename Data>
  class BreadthTraversableContainer : virtual public TraversableContainer<Data> {
    private:

    protected:

    public:

      // Destructor
      virtual ~BreadthMappableContainer() = default;

      // Copy assignment
      BreadthMappableContainer& operator=(const BreadthMappableContainer&) = delete;

      // Move assignment
      BreadthMappableContainer& operator=(BreadthMappableContainer&&) noexcept = delete;

      // Comparison operators
      bool operator==(const BreadthMappableContainer&) const noexcept = delete;
      bool operator!=(const BreadthMappableContainer&) const noexcept = delete;

      // Specific member function
      using typename TraversableContainer<Data>::TraverseFun;

      virtual void BreadthTraverse(TraverseFun) const = 0;

      template <typename Accumulator>
      using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

      template <typename Accumulator>
      inline Accumulator BreadthFold(FoldFun<Accumulator> function, Accumulator base) const;

      // Specific member function (inherited from TraversableContainer)
      inline void Traverse(const TraverseFun) const override{
        BreadthTraverse(function);
      };
  };
}

#include "traversable.cpp"

#endif