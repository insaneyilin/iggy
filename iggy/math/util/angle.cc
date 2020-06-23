// Copyright 2020 insaneyilin All Rights Reserved.
#include "iggy/math/util/angle.h"
#include "iggy/math/util/sin_table.h"

namespace iggy {
namespace math {
namespace util {

float sin(Angle8 a) {
  Angle16 b(static_cast<int16_t>(a.raw_value() << 8));
  return sin(b);
}

float cos(Angle8 a) {
  Angle16 b(static_cast<int16_t>(a.raw_value() << 8));
  return cos(b);
}

float tan(Angle8 a) {
  Angle16 b(static_cast<int16_t>(a.raw_value() << 8));
  return tan(b);
}

float sin(Angle16 a) {
  int16_t idx = a.raw_value();

  if (idx < -Angle16::RAW_PI_2) {
    idx = static_cast<int16_t>(idx + Angle16::RAW_PI);
    return -SIN_TABLE[idx % kSinTableSize];
  }
  if (idx < 0) {
    return -SIN_TABLE[(-idx) % kSinTableSize];
  }
  if (idx < Angle16::RAW_PI_2) {
    return SIN_TABLE[idx % kSinTableSize];
  }
  idx = static_cast<int16_t>(Angle16::RAW_PI - idx);
  return SIN_TABLE[idx % kSinTableSize];
}

float cos(Angle16 a) {
  Angle16 b(static_cast<int16_t>(Angle16::RAW_PI_2 - a.raw_value()));
  return sin(b);
}

float tan(Angle16 a) {
  return sin(a) / cos(a);
}

}  // namespace util
}  // namespace math
}  // namespace iggy

