// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "iggy/math/util/mean_filter.h"

namespace iggy {
namespace math {
namespace util {

TEST(MeanFilterTest, BasicTest) {
  {
    MeanFilter mf(1);
    EXPECT_DOUBLE_EQ(mf.Update(2.0), 2.0);
    EXPECT_DOUBLE_EQ(mf.Update(3.0), 3.0);
  }
  {
    MeanFilter mf(3);
    EXPECT_DOUBLE_EQ(mf.Update(2.0), 2.0);
    EXPECT_DOUBLE_EQ(mf.Update(3.0), 2.5);
    EXPECT_DOUBLE_EQ(mf.Update(3.0), 8.0 / 3);
  }
  {
    MeanFilter mf(3, true);
    EXPECT_DOUBLE_EQ(mf.Update(1.0), 1.0);
    EXPECT_DOUBLE_EQ(mf.Update(5.0), 3.0);
    EXPECT_DOUBLE_EQ(mf.Update(2.0), 2.0);
    EXPECT_DOUBLE_EQ(mf.Update(3.0), 3.0);
    EXPECT_DOUBLE_EQ(mf.Update(4.0), 3.0);
  }
}

TEST(MeanFilterTest, AnotherTest) {
  MeanFilter mean_filter(5, true);
  EXPECT_DOUBLE_EQ(mean_filter.Update(5.0), 5.0);
  EXPECT_DOUBLE_EQ(mean_filter.Update(3.0), 4.0);
  EXPECT_DOUBLE_EQ(mean_filter.Update(8.0), 5.0);
  EXPECT_DOUBLE_EQ(mean_filter.Update(9.0), 6.5);
  EXPECT_DOUBLE_EQ(mean_filter.Update(7.0), 20.0 / 3.0);
  EXPECT_DOUBLE_EQ(mean_filter.Update(2.0), 6.0);
  EXPECT_DOUBLE_EQ(mean_filter.Update(1.0), 17.0 / 3.0);
  EXPECT_DOUBLE_EQ(mean_filter.Update(4.0), 13.0 / 3.0);
}

}  // namespace util
}  // namespace math
}  // namespace iggy
