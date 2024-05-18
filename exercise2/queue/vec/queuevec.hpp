#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

#include "../queue.hpp"
#include "../../vector/vector.hpp"

#define INITIAL_CAPACITY 16
#define REDUCTION_THRESHOLD 4
#define EXPANSION_FACTOR 2
#define REDUCTION_FACTOR 2

namespace lasd {

  template <typename Data> class QueueVec : virtual public Queue<Data>, virtual protected Vector<Data> {
    private:

    protected:
      using Vector<Data>::elements;
      using Container::size;
      unsigned long head = 0;
      unsigned long tail = 0;
      unsigned long numElements = 0;

    public:
      // Default constructor
      QueueVec();

      // Specific constructor
      QueueVec(const TraversableContainer<Data>&);
      QueueVec(MappableContainer<Data>&&);

      // Copy constructor
      QueueVec(const QueueVec&);

      // Move constructor
      QueueVec(QueueVec&&) noexcept;

      // Destructor
      virtual ~QueueVec() = default;

      // Copy assignment
      inline QueueVec& operator=(const QueueVec&);

      // Move assignment
      inline QueueVec& operator=(QueueVec&&) noexcept;

      // Comparison operators
      inline bool operator==(const QueueVec&) const noexcept;
      inline bool operator!=(const QueueVec&) const noexcept;

      // Specific member functions (inherited from Queue)
      inline const Data& Head() const override;
      inline Data& Head() override;
      inline void Dequeue() override;
      inline Data HeadNDequeue() override;
      inline void Enqueue(const Data&) override;
      inline void Enqueue(Data&&) override;

      // Specific member functions (inherited from Container)
      inline bool Empty() const noexcept override;

      inline unsigned long Size() const noexcept override;

      // Specific member function (inherited from ClearableContainer)
      inline void Clear() override;
      inline void Resize(unsigned long) override;

    protected:
      // Auxiliary functions, if necessary!
  };
}

#include "queuevec.cpp"

#endif