// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "iggy/math/util/math_util.h"

namespace iggy {
namespace math {
namespace util {

TEST(MathUtilTest, SqrTest) {
  EXPECT_EQ(MathUtil::Sqr(1), 1);
  EXPECT_EQ(MathUtil::Sqr(2), 4);
  EXPECT_EQ(MathUtil::Sqr(0), 0);

  EXPECT_NEAR(MathUtil::Sqr(1.0), 1.0, 1e-6);
  EXPECT_NEAR(MathUtil::Sqr(1.5), 2.25, 1e-6);

  EXPECT_NEAR(MathUtil::Sqr(1.f), 1.f, 1e-6f);
  EXPECT_NEAR(MathUtil::Sqr(1.5f), 2.25f, 1e-6f);
}

TEST(MathUtilTest, AngleConvertionTest) {
  EXPECT_NEAR(MathUtil::Deg2Rad(1.f), 0.01745f, 1e-3);
  EXPECT_NEAR(MathUtil::Rad2Deg(1.f), 57.2957f, 1e-3);

  EXPECT_NEAR(MathUtil::WrapAngle(6.9813), 0.6981, 1e-3);
  EXPECT_NEAR(MathUtil::WrapAngle(-0.87266), 5.4105, 1e-3);
  EXPECT_NEAR(MathUtil::NormalizeAngleToPI(6.9813), 0.6981, 1e-3);
  EXPECT_NEAR(MathUtil::AngleDiff(-3.1415926, 3.1415926), 0.0, 1e-3);
}

TEST(MathUtilTest, FloatCompareTest) {
  EXPECT_EQ(MathUtil::FloatCompare(1.0, 1.0), 0);
  EXPECT_EQ(MathUtil::FloatCompare(2.1f, 2.1f), 0);
  EXPECT_EQ(MathUtil::FloatCompare(0.0001, 0.00011), -1);
  EXPECT_EQ(MathUtil::FloatCompare(0.0011f, 0.0001f), 1);
  EXPECT_TRUE(MathUtil::FloatEqual(0.10001, 0.1, 1e-5));
  EXPECT_FALSE(MathUtil::FloatEqual(0.10001, 0.1, 1e-6));
  EXPECT_TRUE(MathUtil::FloatLess(0.0001, 0.00011));
  EXPECT_TRUE(MathUtil::FloatGreater(0.0021, 0.00011));
}

TEST(MathUtilTest, GaussianTest) {
  EXPECT_NEAR(MathUtil::Gaussian(1.0, 0.0, 2.0), 0.17603, 1e-5);
}

TEST(MathUtilTest, CartesianPolarConvertionTest) {
  double x = 0.0;
  double y = 0.0;
  double r = 0.0;
  double theta = 0.0;
  MathUtil::Cartesian2Polar(x, y, &r, &theta);
  EXPECT_NEAR(r, 0.0, 1e-6);
  EXPECT_NEAR(theta, 0.0, 1e-6);

  x = 1.0;
  y = 2.0;
  MathUtil::Cartesian2Polar(x, y, &r, &theta);
  EXPECT_NEAR(r, 2.23606, 1e-5);
  EXPECT_NEAR(theta, 1.10714, 1e-5);

  r = 10.0;
  theta = MathUtil::Deg2Rad(60.0);
  MathUtil::Polar2Cartesian(r, theta, &x, &y);
  EXPECT_NEAR(x, 5, 1e-3);
  EXPECT_NEAR(y, 8.66, 1e-3);
}

TEST(MathUtilTest, ClampTest) {
  EXPECT_EQ(MathUtil::Clamp(-1, 0, 2), 0);
  EXPECT_EQ(MathUtil::Clamp(10, 0, 2), 2);
  EXPECT_NEAR(MathUtil::Clamp(-1.0, 0.1, 2.0), 0.1, 1e-3);
  EXPECT_NEAR(MathUtil::Clamp(100.0, 0.0, 2.5), 2.5, 1e-3);
}

TEST(MathUtilTest, CrossProdTest) {
  double x0 = 1.0;
  double y0 = 2.0;
  double x1 = 4.0;
  double y1 = 5.0;
  EXPECT_NEAR(MathUtil::CrossProd(x0, y0, x1, y1), -3.0, 1e-5);
}

TEST(MathUtilTest, DotProdTest) {
  double x0 = 1.0;
  double y0 = 2.0;
  double x1 = 4.0;
  double y1 = 5.0;
  EXPECT_NEAR(MathUtil::DotProd(x0, y0, x1, y1), 14.0, 1e-5);
}

TEST(MathUtilTest, CalculateMeanAndVarianceTest) {
  std::vector<double> data1 = {1.0, 1.0, 1.0, 1.0};
  double mean = 0.0;
  double var = 0.0;
  MathUtil::CalculateMeanAndVariance(data1, &mean, &var);
  EXPECT_NEAR(mean, 1.0, 1e-5);
  EXPECT_NEAR(var, 0.0, 1e-5);

  std::vector<double> data2 = {1.0, 2.0, 3.0, 4.0, 5.0};
  MathUtil::CalculateMeanAndVariance(data2, &mean, &var);
  EXPECT_NEAR(mean, 3.0, 1e-5);
  EXPECT_NEAR(var, 2.0, 1e-5);
}

}  // namespace util
}  // namespace math
}  // namespace iggy
