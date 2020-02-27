// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_MATH_UTIL_MATH_UTIL_H_
#define IGGY_MATH_UTIL_MATH_UTIL_H_

#include <Eigen/Core>

#define _USE_MATH_DEFINES
#include <cmath>

#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

#include "iggy/common/util/macros.h"

namespace iggy {
namespace math {
namespace util {

class MathUtil {
 public:
  // square
  template<typename FloatType>
  static FloatType Sqr(const FloatType value) {
    return value * value;
  }

  // degree to radian
  template<typename FloatType>
  static FloatType Deg2Rad(const FloatType angle_degrees) {
    return angle_degrees * static_cast<FloatType>(s_deg2rad_factor_);
  }

  // radian to degree
  template<typename FloatType>
  static FloatType Rad2Deg(const FloatType angle_radians) {
    return angle_radians * static_cast<FloatType>(s_rad2deg_factor_);
  }

  template<typename FloatType>
  static FloatType PI() {
    return static_cast<FloatType>(s_pi_);
  }

  // Wrap angle to [0, 2 * PI)
  template<typename FloatType>
  static FloatType WrapAngle(const FloatType angle) {
    const FloatType new_angle = std::fmod(angle,
        static_cast<FloatType>(s_2pi_));
    return new_angle < 0 ?
        new_angle + static_cast<FloatType>(s_2pi_) :
        new_angle;
  }

  // Wrap angle to [-PI, PI)
  template<typename FloatType>
  static FloatType NormalizeAngleToPI(const FloatType angle) {
    FloatType new_angle = std::fmod(angle + static_cast<FloatType>(s_pi_),
        static_cast<FloatType>(s_2pi_));
    if (new_angle < 0.0) {
      new_angle += static_cast<FloatType>(s_2pi_);
    }
    return new_angle - static_cast<FloatType>(s_pi_);
  }

  template<typename FloatType>
  static FloatType AngleDiff(const FloatType from, const FloatType to) {
    return NormalizeAngleToPI(to - from);
  }

  template<typename FloatType>
  static int FloatCompare(const FloatType a, const FloatType b) {
    FloatType diff = a - b;
    if (diff < static_cast<FloatType>(0.0)) {
      return -1;
    } else if (diff > static_cast<FloatType>(0.0)) {
      return 1;
    }
    return 0;
  }

  template<typename FloatType>
  static bool FloatEqual(const FloatType a, const FloatType b,
      const FloatType eps) {
    if (std::fabs(a - b) < eps) {
      return true;
    }
    return false;
  }

  template<typename FloatType>
  static bool FloatLess(const FloatType a, const FloatType b) {
    return FloatCompare(a, b) == -1;
  }

  template<typename FloatType>
  static bool FloatGreater(const FloatType a, const FloatType b) {
    return FloatCompare(a, b) == 1;
  }

  template<typename FloatType>
  static FloatType Gaussian(const FloatType x, const FloatType mu,
      const FloatType std) {
    return (1.0 / std::sqrt(static_cast<FloatType>(s_2pi_) * std * std)) *
        std::exp(-(x - mu) * (x - mu) / (2 * std * std));
  }

  template<typename FloatType>
  static void Cartesian2Polar(FloatType x, FloatType y, FloatType *r,
      FloatType *theta) {
    *r = std::sqrt(x * x + y * y);
    *theta = std::atan2(y, x);
  }

  template<typename FloatType>
  static void Polar2Cartesian(FloatType r, FloatType theta_rad, FloatType *x,
      FloatType *y) {
    *x = r * std::cos(theta_rad);
    *y = r * std::sin(theta_rad);
  }

  // Clamp a value between two bounds
  template <typename T>
  static T Clamp(const T value, T bound1, T bound2) {
    if (bound1 > bound2) {
      std::swap(bound1, bound2);
    }
    return (value < bound1) ? bound1 :
        ((value > bound2) ? bound2 : value);
  }

  template <typename FloatType>
  static FloatType CrossProd(const FloatType x0, const FloatType y0,
      const FloatType x1, const FloatType y1) {
    return x0 * y1 - x1 * y0;
  }

  template <typename FloatType>
  static FloatType DotProd(const FloatType x0, const FloatType y0,
      const FloatType x1, const FloatType y1) {
    return x0 * x1 + y0 * y1;
  }

  template <typename FloatType>
  static void CalculateMeanAndVariance(const std::vector<FloatType> &data,
      FloatType *mean, FloatType *variance) {
    if (data.size() == 0) {
      *mean = 0;
      *variance = 0;
      return;
    }
    FloatType sum = std::accumulate(data.begin(), data.end(),
        static_cast<FloatType>(0));
    *mean = sum / data.size();

    std::vector<FloatType> diff(data.size());
    std::transform(data.begin(), data.end(), diff.begin(),
        [mean](FloatType x) {
      return x - *mean;
    });
    FloatType sum_of_diff_sqrs = std::inner_product(diff.begin(), diff.end(),
        diff.begin(), static_cast<FloatType>(0));
    *variance = sum_of_diff_sqrs / data.size();
  }

 private:
  static double s_pi_;
  static double s_2pi_;
  static double s_deg2rad_factor_;
  static double s_rad2deg_factor_;

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(MathUtil);
};

}  // namespace util
}  // namespace math
}  // namespace iggy

#endif  // IGGY_MATH_UTIL_MATH_UTIL_H_
