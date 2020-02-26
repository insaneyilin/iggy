// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>

#include "gtest/gtest.h"

#include "iggy/common/util/macros.h"

namespace iggy {
namespace common {
namespace util {

class Sample {
 public:
  DECLARE_SINGLETON(Sample);

 public:
  static int s_instance_count_;
};

int Sample::s_instance_count_ = 0;
Sample::Sample() {
  ++Sample::s_instance_count_;
}

TEST(SingletonTest, InstanceCount) {
  EXPECT_EQ(0, Sample::s_instance_count_);

  auto inst1 = Sample::Instance();
  EXPECT_EQ(1, Sample::s_instance_count_);

  auto inst2 = Sample::Instance();
  EXPECT_EQ(1, Sample::s_instance_count_);
  EXPECT_TRUE(inst1 == inst2);
}

}  // namespace util
}  // namespace common
}  // namespace iggy
