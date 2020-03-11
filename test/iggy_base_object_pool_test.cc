// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>

#include "gtest/gtest.h"

#include "iggy/base/object_pool.h"

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

}  // namespace base
}  // namespace iggy
