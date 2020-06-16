// Copyright 2020 insaneyilin All Rights Reserved.

#include <vector>
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "iggy/common/util/lru_cache.h"

namespace iggy {
namespace common {
namespace util {

TEST(LRUCache, TestPutAndGet) {
  std::vector<int> keys = {1, 2, 3, 4, 5};
  std::vector<int*> values(5);
  for (int i = 0; i < 5; ++i) {
    values[i] = new int;
    *(values[i]) = (i + 1) * (i + 1);
  }
  LRUCache<int, int> lru_cache(100);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(lru_cache.Put(keys[i], values[i]), nullptr);
  }
  for (int i = 1; i <= 5; ++i) {
    int *val = nullptr;
    EXPECT_TRUE(lru_cache.Get(i, &val));
    EXPECT_EQ(*val, i * i);
    std::list<std::pair<int, int*>> elem_list;
    lru_cache.GetElementList(&elem_list);
    EXPECT_EQ(*(elem_list.begin())->second, i * i);
  }

  for (int i = 0; i < 5; ++i) {
    delete values[i];
  }
}

// TODO(insaneyilin): add more tests

}  // namespace util
}  // namespace common
}  // namespace iggy
