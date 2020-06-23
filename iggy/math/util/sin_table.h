// Copyright 2020 insaneyilin All Rights Reserved.
// Reference: modules/common/math/sin_table.h from ApolloAuto
#ifndef IGGY_MATH_UTIL_SIN_TABLE_H_
#define IGGY_MATH_UTIL_SIN_TABLE_H_

namespace iggy {
namespace math {
namespace util {

// Used by Angle class to speed-up computation of trigonometric functions.
const int kSinTableSize = 16385;
extern const float SIN_TABLE[kSinTableSize];

}  // namespace util
}  // namespace math
}  // namespace iggy

#endif  // IGGY_MATH_UTIL_SIN_TABLE_H_
