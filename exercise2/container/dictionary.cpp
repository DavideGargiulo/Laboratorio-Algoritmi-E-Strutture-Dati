namespace lasd {

  template <typename Data> inline bool
  DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& container) {
      bool result = true;
      container.Traverse([this, &result](const Data& currentData) {
          result &= this->Insert(currentData);
      });
      return result;
  }

  template <typename Data> inline bool
  DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& container) {
      bool result = true;
      container.Map([this, &result](Data& currentData) {
          result &= this->Insert(std::move(currentData));
      });
      return result;
  }

  template <typename Data> inline bool
  DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& container) {
      bool result = true;
      container.Traverse([this, &result](const Data &currentData) {
          result &= this->Remove(currentData);
      });
      return result;
  }

  template <typename Data> inline bool
  DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& container) {
      bool result = false;
      container.Traverse([this, &result](const Data& currentData) {
          result |= this->Insert(currentData);
      });
      return result;
  }

  template <typename Data> inline bool
  DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& container) {
      bool result = false;
      container.Map([this, &result](Data& currentData) {
          result |= this->Insert(std::move(currentData));
      });
      return result;
  }

  template <typename Data> inline bool
  DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& container) {
      bool result = false;
      container.Traverse([this, &result](const Data& currentData) {
          result |= this->Remove(currentData);
      });
      return result;
  }
}