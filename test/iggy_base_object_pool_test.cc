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

}  // namespace base
}  // namespace iggy
