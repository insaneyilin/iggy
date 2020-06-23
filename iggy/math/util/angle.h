// Copyright 2020 insaneyilin All Rights Reserved.
// Reference: modules/common/math/angle.h from ApolloAuto
#ifndef IGGY_MATH_UTIL_ANGLE_H_
#define IGGY_MATH_UTIL_ANGLE_H_

#include <cmath>
#include <cstdint>
#include <limits>

namespace iggy {
namespace math {
namespace util {

/**
 * @class Angle
 * @brief The Angle class uses an integer to represent an angle, and supports
 * commonly-used operations such as addition and subtraction,
 * as well as the use of trigonometric functions.
 *
 * Having a specialized Angle class prevents code repetition, namely for tasks
 * such as computing angle differences or finding equivalent angles in some
 * specified interval, typically [-pi, pi).
 * Representing angles by integers has the following advantages:
 * 1) Finer level of precision control (< means "less precise than"):
 * Angle8 < Angle16 < float < Angle32 < double < Angle64.
 * 2) Angle8 and Angle16 allow super fast trigonometric functions
 * via a 64-KiB lookup table.
 * 3) Higher precision with the same representation size.
 * The use of the Angle class is encouraged.
 * In particular, Angle32 should be used for latitude/longitude (<1cm error).
 * Angle16 is precise enough for localization/object detection.

 * @param T signed integer type
*/
template <typename T>
class Angle {
 public:
  static_assert(std::numeric_limits<T>::is_integer &&
                std::numeric_limits<T>::is_signed,
                "T must be a signed integer type");

  // Constructs an Angle object from an angle in degrees (factory)
  static Angle from_deg(const double deg) {
    return Angle(static_cast<T>(std::lround(deg * DEG_TO_RAW)));
  }

  // Constructs an Angle object from an angle in radians (factory)
  static Angle from_rad(const double rad) {
    return Angle(static_cast<T>(std::lround(rad * RAD_TO_RAW)));
  }

  // Constructs an Angle object from raw internal value
  explicit Angle(const T value = 0) : raw_value_(value) {}

  // Internal representation of pi
  static constexpr T RAW_PI = std::numeric_limits<T>::min();

  // Internal representation of pi/2
  static constexpr T RAW_PI_2 =
      static_cast<T>(-(std::numeric_limits<T>::min() >> 1));

  static constexpr double DEG_TO_RAW = RAW_PI / -180.0;
  static constexpr double RAD_TO_RAW = RAW_PI * -M_1_PI;
  static constexpr double RAW_TO_DEG = -180.0 / RAW_PI;
  static constexpr double RAW_TO_RAD = -M_PI / RAW_PI;

  double to_deg() const {
    return raw_value_ * RAW_TO_DEG;
  }

  double to_rad() const {
    return raw_value_ * RAW_TO_RAD;
  }

  Angle operator+=(Angle that) {
    raw_value_ = static_cast<T>(raw_value_ + that.raw_value_);
    return *this;
  }

  Angle operator-=(Angle that) {
    raw_value_ = static_cast<T>(raw_value_ - that.raw_value_);
    return *this;
  }

  template <typename Scalar>
  Angle operator*=(Scalar s) {
    raw_value_ = static_cast<T>(std::lround(raw_value_ * s));
    return *this;
  }

  template <typename Scalar>
  Angle operator/=(Scalar s) {
    raw_value_ = static_cast<T>(std::lround(raw_value_ / s));
    return *this;
  }

  T raw_value() {
    return raw_value_;
  }

 private:
  T raw_value_;
};

template <typename T>
Angle<T> operator+(Angle<T> lhs, Angle<T> rhs) {
  lhs += rhs;
  return lhs;
}

template <typename T>
Angle<T> operator-(Angle<T> lhs, Angle<T> rhs) {
  lhs -= rhs;
  return lhs;
}

template <typename T, typename Scalar>
Angle<T> operator*(Angle<T> lhs, Scalar rhs) {
  lhs *= rhs;
  return lhs;
}

template <typename T, typename Scalar>
Angle<T> operator*(Scalar lhs, Angle<T> rhs) {
  rhs *= lhs;
  return rhs;
}

template <typename T, typename Scalar>
Angle<T> operator/(Angle<T> lhs, Scalar rhs) {
  lhs /= rhs;
  return lhs;
}

template <typename T>
double operator/(Angle<T> lhs, Angle<T> rhs) {
  return static_cast<double>(lhs.raw_value()) / rhs.raw_value();
}

template <typename T>
bool operator==(Angle<T> lhs, Angle<T> rhs) {
  return lhs.raw_value() == rhs.raw_value();
}

template <typename T>
bool operator!=(Angle<T> lhs, Angle<T> rhs) {
  return !(lhs == rhs);
}

using Angle8 = Angle<int8_t>;
using Angle16 = Angle<int16_t>;
using Angle32 = Angle<int32_t>;
using Angle64 = Angle<int64_t>;

// Fast trigonometric functions. Single precision is sufficient for Angle16 and
// Angle8.
float sin(Angle8 a);
float cos(Angle8 a);
float tan(Angle8 a);
float sin(Angle16 a);
float cos(Angle16 a);
float tan(Angle16 a);

}  // namespace util
}  // namespace math
}  // namespace iggy

#endif  // IGGY_MATH_UTIL_ANGLE_H_

