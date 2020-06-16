// Copyright 2020 insaneyilin All Rights Reserved.

#include "iggy/base/worker_thread.h"

namespace iggy {
namespace base {

WorkerThread::~WorkerThread() {
  Release();
}

void WorkerThread::Bind(const std::function<bool()> &func) {
  func_ = func;
}

void WorkerThread::Start() {
  if (thread_ == nullptr) {
    thread_.reset(new std::thread(&WorkerThread::MainLoop, this));
  }
  std::lock_guard<std::mutex> lock(mutex_);
  working_flag_ = false;
  stop_flag_ = false;
}

void WorkerThread::WakeUp() {
  {
    std::lock_guard<std::mutex> lock(mutex_);
    working_flag_ = true;
  }
  cv_.notify_one();
}

void WorkerThread::Join() {
  std::unique_lock<std::mutex> lock(mutex_);
  cv_.wait(lock, [&]() {
    return !working_flag_;
  });
}

void WorkerThread::Release() {
  if (thread_ == nullptr) {
    return;
  }
  {
    std::lock_guard<std::mutex> lock(mutex_);
    working_flag_ = true;
    stop_flag_ = true;
  }
  cv_.notify_one();
  thread_->join();
  thread_.reset(nullptr);
}

void WorkerThread::MainLoop() {
  while (true) {
    {
      std::unique_lock<std::mutex> lock(mutex_);
      cv_.wait(lock, [&]() {
        return working_flag_;
      });
    }
    if (stop_flag_) {
      break;
    }
    func_();
    {
      std::lock_guard<std::mutex> lock(mutex_);
      working_flag_ = false;
    }
    cv_.notify_one();
  }
}

}  // namespace base
}  // namespace iggy

