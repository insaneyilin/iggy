// Copyright 2020 insaneyilin All Rights Reserved.

#ifndef IGGY_COMMON_UTIL_LRU_CACHE_H_
#define IGGY_COMMON_UTIL_LRU_CACHE_H_

#include <list>
#include <unordered_map>
#include <utility>

namespace iggy {
namespace common {
namespace util {

template <class K, class T>
class LRUCache {
 public:
  using ListIterator = typename std::list<std::pair<K, T*>>::iterator;
  using ListReverseIterator =
      typename std::list<std::pair<K, T*>>::reverse_iterator;
  using MapIterator =
      typename std::unordered_map<K, ListIterator>::iterator;

  explicit LRUCache(std::size_t capacity) : capacity_(capacity) {}
  virtual ~LRUCache() {}

  bool Get(const K &key, T **value);

  bool GetSilent(const K &key, T **value);

  T* Put(const K &key, T *value);

  T* Remove(const K &key);

  T* RemoveLeastRecentlyUsedElement();

  // check whether element exists in the cache, if it exists, move it to the
  // head.
  bool Check(const K &key);

  bool SetCapacity(std::size_t capacity) {
    if (list_.size() > capacity) {
      return false;
    }
    capacity_ = capacity;
    return true;
  }

  std::size_t Size() const {
    return list_.size();  // std::list::size() is O(1) after C++11
  }

  std::size_t Capacity() const {
    return capacity_;
  }

  void GetElementList(std::list<std::pair<K, T*>> *list) const {
    *list = list_;
  }

 protected:
  virtual bool Release(T *value) {
    return true;
  }

 private:
  std::size_t capacity_;
  std::unordered_map<K, ListIterator> hash_table_;
  std::list<std::pair<K, T*>> list_;
};

}  // namespace util
}  // namespace common
}  // namespace iggy

#include "iggy/common/util/lru_cache.hpp"

#endif  // IGGY_COMMON_UTIL_LRU_CACHE_H_

