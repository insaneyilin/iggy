// Copyright 2020 insaneyilin All Rights Reserved.
// Reference: modules/perception/lib/thread/thread_worker.h from ApolloAuto

#ifndef IGGY_BASE_WORKER_THREAD_H_
#define IGGY_BASE_WORKER_THREAD_H_

#include <thread>  // NOLINT
#include <mutex>  // NOLINT
#include <condition_variable>  // NOLINT
#include <functional>
#include <memory>

namespace iggy {
namespace base {

class WorkerThread {
 public:
  WorkerThread() = default;
  ~WorkerThread();

  // bind a bool returned function to the thread
  // should be called before Start()
  void Bind(const std::function<bool()> &func);

  // start the thread main working loop
  void Start();

  // wake up the thread to work
  void WakeUp();

  // wait util the a single execution is done
  void Join();

  // release the thread resources
  void Release();

 private:
  // the main loop of thread
  void MainLoop();

 private:
  std::unique_ptr<std::thread> thread_;
  std::mutex mutex_;
  std::condition_variable cv_;

  bool working_flag_ = false;
  bool stop_flag_ = true;

  std::function<bool()> func_;
};

}  // namespace base
}  // namespace iggy

#endif  // IGGY_BASE_WORKER_THREAD_H_

