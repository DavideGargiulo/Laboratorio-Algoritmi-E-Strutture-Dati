#ifndef QUEUELST_HPP
#define QUEUELST_HPP

#include "../queue.hpp"
#include "../../list/list.hpp"

namespace lasd {

  template <typename Data> class QueueLst : virtual public Queue<Data>, virtual protected List<Data> {
    private:

    protected:
      using List<Data>::size;

    public:
      // Default constructor
      QueueLst() = default;

      // Specific constructor
      explicit QueueLst(const TraversableContainer<Data>&);
      explicit QueueLst(MappableContainer<Data>&&);

      // Copy constructor
      QueueLst(const QueueLst<Data>&);

      // Move constructor
      QueueLst(QueueLst<Data>&&) noexcept;

      // Destructor
      virtual ~QueueLst() = default;

      // Copy assignment
      inline QueueLst& operator=(const QueueLst&);

      // Move assignment
      inline QueueLst& operator=(QueueLst&&) noexcept;

      // Comparison operators
      inline bool operator==(const QueueLst&) const noexcept;
      inline bool operator!=(const QueueLst&) const noexcept;

      // Specific member functions (inherited from Queue)
      inline const Data& Head() const override;
      inline Data& Head() override;
      inline void Dequeue() override;
      inline Data HeadNDequeue() override;
      inline void Enqueue(const Data&) override;
      inline void Enqueue(Data&&) override;

      // Specific member function (inherited from ClearableContainer)
      using List<Data>::Clear;

    protected:
      // Auxiliary functions, if necessary!
  };
}

#include "queuelst.cpp"

#endif