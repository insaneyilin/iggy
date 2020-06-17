// Copyright 2020 insaneyilin All Rights Reserved.
#include "iggy/common/util/lru_cache.h"

namespace iggy {
namespace common {
namespace util {

template <typename K, typename T>
bool LRUCache<K, T>::Get(const K &key, T **value) {
  MapIterator itr = hash_table_.find(key);
  if (itr == hash_table_.end()) {
    return false;
  }
  // move to list head
  list_.splice(list_.begin(), list_, itr->second);
  *value = itr->second->second;
  return true;
}

template <typename K, typename T>
bool LRUCache<K, T>::GetSilent(const K &key, T **value) {
  MapIterator itr = hash_table_.find(key);
  if (itr == hash_table_.end()) {
    return false;
  }
  // not move to list head
  *value = itr->second->second;
  return true;
}

template <typename K, typename T>
T* LRUCache<K, T>::Put(const K &key, T *value) {
  if (value == nullptr) {
    return nullptr;
  }
  T *elem_remove = nullptr;
  MapIterator itr = hash_table_.find(key);
  // key exists in the cache
  if (itr != hash_table_.end()) {
    list_.splice(list_.begin(), list_, itr->second);
    elem_remove = itr->second->second;
    if (elem_remove == value) {
      return nullptr;
    }
    if (Release(elem_remove)) {
      itr->second->second = value;
    } else {
      elem_remove = value;
    }
    return elem_remove;
  }
  // cache is full
  if (hash_table_.size() >= capacity_) {
    elem_remove = RemoveLeastRecentlyUsedElement();
  }
  list_.emplace_front(key, value);
  hash_table_[key] = list_.begin();

  return elem_remove;
}

template <typename K, typename T>
T* LRUCache<K, T>::Remove(const K &key) {
  T *elem_remove = nullptr;
  MapIterator itr = hash_table_.find(key);
  if (itr != hash_table_.end() && Release(itr->second->second)) {
    elem_remove = itr->second->second;
    list_.erase(itr->second);
    hash_table_.erase(itr);
  }
  return elem_remove;
}

template <typename K, typename T>
T* LRUCache<K, T>::RemoveLeastRecentlyUsedElement() {
  if (list_.empty()) {
    return nullptr;
  }
  T *elem_remove = nullptr;
  ListReverseIterator ritr = list_.rbegin();
  if (Release(ritr->second)) {
    elem_remove = ritr->second;
    hash_table_.erase(ritr->first);
    ritr = ListReverseIterator(list_.erase((++ritr).base()));
  }
  return elem_remove;
}

template <typename K, typename T>
bool LRUCache<K, T>::Check(const K &key) {
  MapIterator itr = hash_table_.find(key);
  if (itr != hash_table_.end()) {
    list_.splice(list_.begin(), list_, itr->second);
  }
  return itr != hash_table_.end();
}

}  // namespace util
}  // namespace common
}  // namespace iggy

