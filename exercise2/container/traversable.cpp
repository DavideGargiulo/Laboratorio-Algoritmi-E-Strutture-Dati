namespace lasd {

  template <typename Data, typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Data>
  template <typename Accumulator> inline Accumulator 
  TraversableContainer<Data>::Fold(FoldFun<Accumulator> function, Accumulator base) const {
    Traverse([&base, function](const Data &currentData) { 
      base = function(currentData, base); 
    });
    return base;
  }

  template <typename Data> inline bool
  TraversableContainer<Data>::Exists(const Data &data) const noexcept {
    bool exists = false;
    Traverse([data, &exists](const Data &currentData) { 
      exists |= (data == currentData); 
    });
    return exists;
  }

  template <typename Data>
  template <typename Accumulator> inline Accumulator
  PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> function, Accumulator base) const {
    PreOrderTraverse([&base, function](const Data &currentData) { 
      base = function(currentData, base); 
    });
    return base;
  }

  template <typename Data>
  template <typename Accumulator> inline Accumulator
  PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> function, Accumulator base) const {
    PostOrderTraverse([&base, &function](const Data &currentData) { 
      base = function(currentData, base); 
    });
    return base;
  }
}