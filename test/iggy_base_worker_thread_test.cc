// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "gtest/gtest.h"

#include "iggy/base/worker_thread.h"

namespace iggy {
namespace base {


TEST(WorkerThreadTest, Test1) {
  WorkerThread worker;
  worker.Bind([&]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return false;
  });
  worker.Start();
  int cnt = 0;
  for (int i = 0; i < 10; ++i) {
    worker.WakeUp();
    ++cnt;
    worker.Join();
  }
  worker.Release();
  EXPECT_EQ(cnt, 10);
}

}  // namespace base
}  // namespace iggy
