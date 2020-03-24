// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>
#include <atomic>
#include <thread>  // NOLINT
#include <chrono>  // NOLINT
#include <iostream>

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

TEST(BoundedConcurrentQueueTest, PopTest) {
  BoundedConcurrentQueue<int> q(100);
  EXPECT_TRUE(q.Empty());
  int val = 0;
  for (int i = 1; i <= 100; ++i) {
    EXPECT_TRUE(q.Push(i));
    EXPECT_EQ(q.Size(), 1);
    EXPECT_TRUE(q.Pop(&val));
    EXPECT_EQ(val, i);
    EXPECT_TRUE(q.Empty());
  }
}

TEST(BoundedConcurrentQueueTest, WaitPopTest) {
  BoundedConcurrentQueue<int> q(100);
  q.Push(10);
  std::thread t([&]() {
    int value = 0;
    q.WaitPop(&value);
    EXPECT_EQ(10, value);
    q.WaitPop(&value);
    EXPECT_EQ(100, value);
  });
  q.Push(100);
  t.join();
}

TEST(BoundedConcurrentQueueTest, WaitPushTest) {
  BoundedConcurrentQueue<int> q(2);
  std::thread t([&]() {
    q.WaitPush(1);
    EXPECT_EQ(q.Size(), 1);
    q.WaitPush(2);
    EXPECT_EQ(q.Size(), 2);
    q.WaitPush(3);
    EXPECT_EQ(q.Size(), 2);
  });
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  int val = 0;
  EXPECT_TRUE(q.Pop(&val));
  t.join();
}

}  // namespace base
}  // namespace iggy
