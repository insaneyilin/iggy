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

  virtual bool Push(const T &element) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.emplace(element);
    cv_.notify_one();
    return true;
  }

  virtual bool WaitPop(T *element) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() {
      return !queue_.empty();
    });
    if (break_all_wait_) {
      return false;
    }
    *element = std::move(queue_.front());
    queue_.pop();
    return true;
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

  virtual void BreakAllWait() {
    break_all_wait_ = true;
    cv_.notify_all();
  }

 protected:
  std::mutex mutex_;
  std::queue<T> queue_;
  std::condition_variable cv_;
  bool break_all_wait_ = false;

 private:
  DISALLOW_MOVE(ConcurrentQueue);
  DISALLOW_COPY_AND_ASSIGN(ConcurrentQueue);
};

}  // namespace base
}  // namespace iggy

#endif  // IGGY_BASE_CONCURRENT_QUEUE_H_
