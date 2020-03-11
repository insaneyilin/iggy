// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "iggy/base/object_pool.h"
#include "iggy/common/time/perf_timer.h"

namespace iggy {
namespace base {

struct TestNode {
  TestNode() : inited(true) {}
  ~TestNode() {
    inited = false;
  }
  explicit TestNode(int val) : value(val), inited(true) {}

  int value = 0;
  bool inited = false;
};

struct BigNode {
  BigNode() {
    for (int i = 0; i < 100000; ++i) {
      data.push_back(1.0 * i);
    }
  }
  ~BigNode() {}

  std::vector<double> data;
};

TEST(ObjectPoolTest, CreateTest) {
  size_t capacity = 100;
  ObjectPool<TestNode> pool1(capacity, [](TestNode*) {});
  {
    auto obj = pool1.GetObjectSharedPtr();
    EXPECT_TRUE(obj->inited);
    EXPECT_EQ(obj->value, 0);
  }

  ObjectPool<TestNode> pool2(capacity, [](TestNode*) {}, 3);
  {
    auto obj = pool2.GetObjectSharedPtr();
    EXPECT_TRUE(obj->inited);
    EXPECT_EQ(obj->value, 3);
  }

  ObjectPool<TestNode> pool3(capacity, [](TestNode *node) {
    node->inited = false;
    node->value = -1;
  }, 3);
  {
    auto obj = pool3.GetObjectSharedPtr();
    EXPECT_FALSE(obj->inited);
    EXPECT_EQ(obj->value, -1);
  }
}

TEST(ObjectPoolTest, CapacityTest) {
  const size_t orig_capacity = 3;
  ObjectPool<TestNode> pool1(orig_capacity, [](TestNode*) {});
  {
    EXPECT_EQ(pool1.Capacity(), 3);
    EXPECT_EQ(pool1.FreeQueueSize(), 3);

    auto obj1 = pool1.GetObjectSharedPtr();
    EXPECT_EQ(pool1.FreeQueueSize(), 2);

    auto obj2 = pool1.GetObjectSharedPtr();
    EXPECT_EQ(pool1.FreeQueueSize(), 1);

    auto obj3 = pool1.GetObjectSharedPtr();
    EXPECT_EQ(pool1.FreeQueueSize(), 0);

    auto obj_null = pool1.GetObjectSharedPtr();
    EXPECT_EQ(obj_null, nullptr);

    pool1.Extend(3, [](TestNode*) {});
    EXPECT_EQ(pool1.Capacity(), 6);
    EXPECT_EQ(pool1.FreeQueueSize(), 3);

    auto obj4 = pool1.GetObjectSharedPtr();
    EXPECT_EQ(pool1.FreeQueueSize(), 2);
  }
  EXPECT_EQ(pool1.Capacity(), 6);
  EXPECT_EQ(pool1.FreeQueueSize(), 6);
}

TEST(ObjectPoolTest, PerfTest) {
  const size_t capacity = 100;
  ObjectPool<BigNode> pool1(capacity, [](BigNode*) {});
  EXPECT_EQ(pool1.Capacity(), 100);
  EXPECT_EQ(pool1.FreeQueueSize(), 100);

  std::vector<std::shared_ptr<BigNode> > obj_vec(100);
  common::time::ClockTimer timer;
  timer.Start();
  for (int i = 0; i < 100; ++i) {
    obj_vec[i] = pool1.GetObjectSharedPtr();
  }
  auto elapsed_time_use_pool = timer.End("use pool");

  for (int i = 0; i < 100; ++i) {
    obj_vec[i].reset(new BigNode);
  }
  auto elapsed_time_use_new = timer.End("use new");
  EXPECT_LT(elapsed_time_use_pool, elapsed_time_use_new);
}

}  // namespace base
}  // namespace iggy
