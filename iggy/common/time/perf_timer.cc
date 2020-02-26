// Copyright 2020 insaneyilin All Rights Reserved.

#include "iggy/common/time/perf_timer.h"

namespace iggy {
namespace common {
namespace time {

void ClockTimer::Start() {
  start_time_ = std::chrono::high_resolution_clock::now();
}

float ClockTimer::End(const std::string &msg) {
  end_time_ = std::chrono::high_resolution_clock::now();
  auto diff = end_time_ - start_time_;
  float elapsed_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
  std::cerr << "TIMER " << msg << " elapsed_time: " << elapsed_time
      << " ms" << std::endl;
  start_time_ = end_time_;
  return elapsed_time;
}

}  // namespace time
}  // namespace common
}  // namespace iggy
