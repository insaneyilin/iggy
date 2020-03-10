// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_BASE_OBJECT_POOL_H_
#define IGGY_BASE_OBJECT_POOL_H_

#include <cstdlib>
#include <queue>
#include <vector>
#include <list>
#include <memory>
#include <functional>
#include <utility>

namespace iggy {
namespace base {

template <typename ObjectType>
class ObjectPool {
 public:
  using InitFunc = std::function<void(ObjectType *)>;

  template <typename... Args>
  explicit ObjectPool(size_t capacity, InitFunc init_func, Args &&... args);

  virtual ~ObjectPool();

  ObjectPool() = delete;

  std::shared_ptr<ObjectType> GetObjectSharedPtr();

  template <typename... Args>
  void Extend(const size_t num, InitFunc init_func, Args &&... args);

 private:
  size_t capacity_ = 0;
  std::queue<ObjectType*> queue_;
  std::vector<ObjectType*> cache_;
  std::list<ObjectType*> extended_cache_;
};

template <typename ObjectType>
template <typename... Args>
ObjectPool<ObjectType>::ObjectPool(size_t capacity, InitFunc init_func,
    Args &&... args) : capacity_(capacity) {
  cache_.resize(capacity_, nullptr);
  for (auto &x : cache_) {
    x = new ObjectType(std::forward<Args>(args)...);
    queue_.push(x);
    init_func(x);
  }
}

template <typename ObjectType>
ObjectPool<ObjectType>::~ObjectPool() {
  for (auto &x : cache_) {
    delete x;
  }
  cache_.clear();
  for (auto &x : extended_cache_) {
    delete x;
  }
  extended_cache_.clear();
}

template <typename ObjectType>
std::shared_ptr<ObjectType> ObjectPool<ObjectType>::GetObjectSharedPtr() {
  ObjectType *ptr = nullptr;
  if (queue_.empty()) {
    return nullptr;
  }
  ptr = queue_.front();
  queue_.pop();
  return std::shared_ptr<ObjectType>(ptr, [&](ObjectType *obj) {
    queue_.push(ptr);
  });
}

template <typename ObjectType>
template <typename... Args>
void ObjectPool<ObjectType>::Extend(const size_t num, InitFunc init_func,
    Args &&... args) {
  for (size_t i = 0; i < num; ++i) {
    ObjectType *ptr = new ObjectType(std::forward<Args>(args)...);
    init_func(ptr);
    extended_cache_.push_back(ptr);
    queue_.push(ptr);
  }
}

}  // namespace base
}  // namespace iggy

#endif  // IGGY_BASE_OBJECT_POOL_H_
