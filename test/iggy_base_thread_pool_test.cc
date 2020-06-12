// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "gtest/gtest.h"

#include "iggy/base/thread_pool.h"
#include "iggy/common/time/perf_timer.h"

namespace iggy {
namespace base {


TEST(ThreadPoolTest, CreateTest) {
  ThreadPool thread_pool(4);
  std::vector<std::future<int>> results;

  thread_pool.Start();
  for (int i = 0; i < 8; ++i) {
    results.emplace_back(thread_pool.Add([i]() {
      std::string str1 = "hello " + std::to_string(i);
      std::cout << str1 << '\n';
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::string str2 = "world " + std::to_string(i);
      std::cout << str2 << '\n';
      return i;
    }));
  }

  for (auto &&result : results) {
    std::cout << result.get() << '\n';
  }
  std::cout << "thread_pool stopped\n";
}

}  // namespace base
}  // namespace iggy
