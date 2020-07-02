// Copyright 2020 insaneyilin All Rights Reserved.
#include <cmath>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "iggy/math/estimation/extended_kalman_filter.h"

namespace iggy {
namespace math {
namespace estimation {

// TODO(guiyilin): add real test
TEST(ExtendedKalmanFilterTest, Simple) {
  ExtendedKalmanFilter<double, 2, 1, 1> ekf_;
}

}  // namespace estimation
}  // namespace math
}  // namespace iggy
