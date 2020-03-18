// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>
#include <thread>  // NOLINT
#include <chrono>  // NOLINT

#include "gtest/gtest.h"

#include "iggy/base/concurrent_queue.h"

namespace iggy {
namespace base {

TEST(ConcurrentQueueTest, PushTest) {
  ConcurrentQueue<int> q;
  EXPECT_TRUE(q.Empty());
  for (int i = 1; i < 100; ++i) {
    q.Push(i);
    EXPECT_EQ(q.Size(), i);
  }
}

TEST(ConcurrentQueueTest, PopTest) {
  ConcurrentQueue<int> q;
  EXPECT_TRUE(q.Empty());
  for (int i = 1; i <= 100; ++i) {
    q.Push(i);
    EXPECT_EQ(q.Size(), i);
  }
  int x = 0;
  for (int i = 1; i <= 100; ++i) {
    EXPECT_TRUE(q.Pop(&x));
    EXPECT_EQ(q.Size(), 100 - i);
    EXPECT_EQ(x, i);
  }
}

TEST(ConcurrentQueueTest, WaitPopTest) {
  ConcurrentQueue<int> q;
  EXPECT_TRUE(q.Empty());
  q.Push(1);
  std::thread t([&]() {
    int value = 0;
    q.WaitPop(&value);
    EXPECT_EQ(1, value);
    q.WaitPop(&value);
    EXPECT_EQ(2, value);
  });
  q.Push(2);
  t.join();
}

TEST(ConcurrentQueueTest, MultiThreadTest) {
  ConcurrentQueue<int> q;
  EXPECT_TRUE(q.Empty());

  bool threads_start = false;
  std::thread t1([&]() {
    while (!threads_start) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    for (int i = 0; i < 10; ++i) {
      q.Push(i);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    q.Push(-1);
    for (int i = 10; i < 20; ++i) {
      q.Push(i);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  });
  std::thread t2([&]() {
    while (!threads_start) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    while (true) {
      int val = 0;
      q.WaitPop(&val);
      if (val < 0) {
        break;
      }
    }
  });

  threads_start = true;
  t1.join();
  t2.join();

  for (int i = 10; i < 20; ++i) {
    int val = 0;
    q.WaitPop(&val);
    EXPECT_EQ(val, i);
  }
}

}  // namespace base
}  // namespace iggy
