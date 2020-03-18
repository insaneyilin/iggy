// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_BASE_CONCURRENT_QUEUE_H_
#define IGGY_BASE_CONCURRENT_QUEUE_H_

#include <queue>
#include <mutex>  // NOLINT
#include <condition_variable>  // NOLINT
#include <thread>  // NOLINT
#include <utility>

#include "iggy/common/util/macros.h"

namespace iggy {
namespace base {

template <typename T>
class ConcurrentQueue {
 public:
  ConcurrentQueue() = default;
  virtual ~ConcurrentQueue() = default;

  virtual void Push(const T &element) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.emplace(element);
    cv_.notify_one();
  }

  virtual void WaitPop(T *element) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() {
      return !queue_.empty();
    });
    *element = std::move(queue_.front());
    queue_.pop();
  }

  virtual bool Pop(T *element) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
      return false;
    }
    *element = std::move(queue_.front());
    queue_.pop();
    return true;
  }

  typename std::queue<T>::size_type Size() {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
  }

  bool Empty() {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
  }

 private:
  std::mutex mutex_;
  std::queue<T> queue_;
  std::condition_variable cv_;

  DISALLOW_MOVE(ConcurrentQueue);
  DISALLOW_COPY_AND_ASSIGN(ConcurrentQueue);
};

}  // namespace base
}  // namespace iggy

#endif  // IGGY_BASE_CONCURRENT_QUEUE_H_
