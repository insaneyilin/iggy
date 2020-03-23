// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>
#include <thread>  // NOLINT
#include <chrono>  // NOLINT

#include "gtest/gtest.h"

#include "iggy/base/bounded_concurrent_queue.h"

namespace iggy {
namespace base {

TEST(BoundedConcurrentQueueTest, PushTest) {
  BoundedConcurrentQueue<int> q(100);
  EXPECT_TRUE(q.Empty());
  for (int i = 1; i <= 100; ++i) {
    EXPECT_TRUE(q.Push(i));
    EXPECT_EQ(q.Size(), i);
  }
  EXPECT_FALSE(q.Push(101));
  EXPECT_EQ(q.Size(), 100);
  EXPECT_TRUE(q.Full());
}

}  // namespace base
}  // namespace iggy
