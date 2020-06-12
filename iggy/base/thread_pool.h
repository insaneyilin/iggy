// Copyright 2020 insaneyilin All Rights Reserved.
// Reference: cyber/base/thread_pool.h from ApolloAuto/apollo

#ifndef IGGY_BASE_THREAD_POOL_H_
#define IGGY_BASE_THREAD_POOL_H_

#include <atomic>
#include <functional>
#include <future>  // NOLINT
#include <memory>
#include <queue>
#include <stdexcept>
#include <thread>  // NOLINT
#include <utility>
#include <vector>
#include <string>

#include "iggy/base/bounded_concurrent_queue.h"

namespace iggy {
namespace base {

class ThreadPool {
 public:
  explicit ThreadPool(std::size_t thread_num, std::size_t max_task_num = 1000);

  bool Start();
  bool Stop();

  template <typename Func, typename... Args>
  auto Add(Func&& f, Args&&... args)
      -> std::future<typename std::result_of<Func(Args...)>::type>;

  ~ThreadPool();

 private:
  std::size_t thread_num_ = 4;
  std::vector<std::thread> workers_;
  std::unique_ptr<BoundedConcurrentQueue<std::function<void()>>> task_queue_;
  std::atomic_bool stop_;
};

ThreadPool::ThreadPool(std::size_t thread_num,
    std::size_t max_task_num) : thread_num_(thread_num), stop_(false) {
  task_queue_.reset(new BoundedConcurrentQueue<std::function<void()>>(
      max_task_num));
}

bool ThreadPool::Start() {
  if (stop_.exchange(false)) {
    return false;
  }
  for (std::size_t i = 0; i < thread_num_; ++i) {
    workers_.emplace_back([this, i]() {
      while (!stop_) {
        std::function<void()> task;
        if (task_queue_->WaitPop(&task)) {
          task();
        }
        // check empty after WaitPop()
        if (task_queue_->Empty()) {
          break;
        }
      }
    });
  }
  return true;
}

bool ThreadPool::Stop() {
  if (stop_.exchange(true)) {
    return false;
  }
  task_queue_->BreakAllWait();
  for (auto &worker : workers_) {
    worker.join();
  }
  return true;
}

template <typename Func, typename... Args>
auto ThreadPool::Add(Func&& f, Args&&... args)
    -> std::future<typename std::result_of<Func(Args...)>::type> {
  using return_type = typename std::result_of<Func(Args...)>::type;

  auto task = std::make_shared<std::packaged_task<return_type()>>(
      std::bind(std::forward<Func>(f), std::forward<Args>(args)...));

  std::future<return_type> res = task->get_future();

  // don't allow enqueueing after stopping the pool
  if (stop_) {
    return std::future<return_type>();
  }
  task_queue_->Push([task]() { (*task)(); });
  return res;
}

ThreadPool::~ThreadPool() {
  Stop();
}

}  // namespace base
}  // namespace iggy

#endif  // IGGY_BASE_THREAD_POOL_H_
