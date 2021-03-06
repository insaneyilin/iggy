// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <thread>  // NOLINT

#include "gtest/gtest.h"

#include "iggy/common/time/perf_timer.h"

namespace iggy {
namespace common {
namespace time {

static void foo() {
  IGGY_PERF_FUNCTION();
  std::this_thread::sleep_for(std::chrono::milliseconds(123));
}

TEST(TimeTest, PerfTimerTest) {
  ClockTimer timer;
  timer.Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_NEAR(timer.End("test1"), 100.f, 5.f);
}

TEST(TimeTest, PerfMacrosTest) {
  IGGY_PERF_BLOCK_START();
  foo();
  EXPECT_NEAR(IGGY_PERF_BLOCK_END("foo"), 123.f, 10.f);
}

}  // namespace time
}  // namespace common
}  // namespace iggy
