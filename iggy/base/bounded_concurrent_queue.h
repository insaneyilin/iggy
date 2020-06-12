// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_BASE_BOUNDED_CONCURRENT_QUEUE_H_
#define IGGY_BASE_BOUNDED_CONCURRENT_QUEUE_H_

#include <queue>
#include <mutex>  // NOLINT
#include <condition_variable>  // NOLINT
#include <thread>  // NOLINT
#include <utility>

#include "iggy/common/util/macros.h"
#include "iggy/base/concurrent_queue.h"

namespace iggy {
namespace base {

template <typename T>
class BoundedConcurrentQueue : public ConcurrentQueue<T> {
 public:
  explicit BoundedConcurrentQueue(size_t capacity)
      : ConcurrentQueue<T>(), capacity_(capacity) {}

  virtual ~BoundedConcurrentQueue() = default;

  virtual bool WaitPush(const T &element) {
    std::unique_lock<std::mutex> lock(this->mutex_);
    cv_full_.wait(lock, [this]() {
      return this->queue_.size() < capacity_;
    });
    if (this->break_all_wait_) {
      return false;
    }
    this->queue_.emplace(element);
    this->cv_.notify_one();
    return true;
  }

  virtual bool Push(const T &element) {
    std::lock_guard<std::mutex> lock(this->mutex_);
    if (this->queue_.size() >= capacity_) {
      return false;
    }
    this->queue_.emplace(element);
    this->cv_.notify_one();
    return true;
  }

  virtual bool WaitPop(T *element) {
    std::unique_lock<std::mutex> lock(this->mutex_);
    this->cv_.wait(lock, [this]() {
      return !this->queue_.empty();
    });
    if (this->break_all_wait_) {
      return false;
    }
    *element = std::move(this->queue_.front());
    this->queue_.pop();
    cv_full_.notify_one();
    return true;
  }

  virtual bool Pop(T *element) {
    std::lock_guard<std::mutex> lock(this->mutex_);
    if (this->queue_.empty()) {
      return false;
    }
    *element = std::move(this->queue_.front());
    this->queue_.pop();
    cv_full_.notify_one();
    return true;
  }

  bool Full() const {
    return this->queue_.size() >= capacity_;
  }

  virtual void BreakAllWait() {
    this->break_all_wait_ = true;
    this->cv_.notify_all();
    this->cv_full_.notify_all();
  }

 protected:
  std::condition_variable cv_full_;
  const size_t capacity_;

  DISALLOW_MOVE(BoundedConcurrentQueue);
  DISALLOW_COPY_AND_ASSIGN(BoundedConcurrentQueue);
};

}  // namespace base
}  // namespace iggy

#endif  // IGGY_BASE_BOUNDED_CONCURRENT_QUEUE_H_
