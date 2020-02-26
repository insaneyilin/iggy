// Copyright 2020 insaneyilin All Rights Reserved.

#ifndef IGGY_COMMON_TIME_PERF_TIMER_H_
#define IGGY_COMMON_TIME_PERF_TIMER_H_

#include <iostream>
#include <numeric>
#include <string>
#include <chrono>  // NOLINT

#include "iggy/common/util/macros.h"

namespace iggy {
namespace common {
namespace time {

class ClockTimer {
  using time_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
 public:
  ClockTimer() = default;
  ~ClockTimer() = default;

  // not thread-safe
  void Start();
  // return in milliseconds
  float End(const std::string &msg);

 private:
  time_t start_time_;
  time_t end_time_;

  DISALLOW_MOVE(ClockTimer);
  DISALLOW_COPY_AND_ASSIGN(ClockTimer);
};

class PerfTimer {
 public:
  explicit PerfTimer(const std::string &msg) : msg_(msg) {
    timer_.Start();
  }
  ~PerfTimer() {
    timer_.End(msg_);
  }

 private:
  ClockTimer timer_;
  std::string msg_;

  DISALLOW_MOVE(PerfTimer);
  DISALLOW_COPY_AND_ASSIGN(PerfTimer);
};

inline std::string GetFunctionName(const std::string &full_name) {
  size_t end = full_name.find("(");
  if (end == std::string::npos) {
    return full_name;
  }
  std::string new_str = full_name.substr(0, end);
  size_t start = new_str.rfind(" ");
  if (start == std::string::npos) {
    return full_name;
  }
  return new_str.substr(start + 1);
}

}  // namespace time
}  // namespace common
}  // namespace iggy

#define IGGY_PERF_FUNCTION()                                                  \
  ::iggy::common::time::PerfTimer(                                            \
      ::iggy::common::time::GetFunctionName(__PRETTY_FUNCTION__))
#define IGGY_PERF_BLOCK_START()                                               \
  ::iggy::common::time::ClockTimer __timer;                                   \
  __timer.Start()
#define IGGY_PERF_BLOCK_END(msg) __timer.End(msg)

#endif  // IGGY_COMMON_TIME_PERF_TIMER_H_
