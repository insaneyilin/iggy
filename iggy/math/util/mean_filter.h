// Copyright 2020 insaneyilin All Rights Reserved.
// Reference: modules/common/filters/mean_filter.h from ApolloAuto

#ifndef IGGY_MATH_UTIL_MEAN_FILTER_H_
#define IGGY_MATH_UTIL_MEAN_FILTER_H_

#include <deque>
#include <utility>
#include <vector>

#include "iggy/common/util/macros.h"

namespace iggy {
namespace math {
namespace util {

class MeanFilter {
 public:
  explicit MeanFilter(const std::size_t window_size,
                      bool discard_max_min = false)
      : window_size_(window_size), discard_max_min_(discard_max_min) {}

  double Update(double measurement);
  double GetMean() const {
    return mean_;
  }
  double GetStddev() const {
    return stddev_;
  }

  std::size_t GetSize() const {
    return values_.size();
  }

 private:
  void Add(double value);
  void RemoveOldestValue();
  bool GetMaxMin(double *max_val, double *min_val,
                 std::size_t *max_time, std::size_t *min_time) const;
  bool ShouldPopOldestCandidate(const std::size_t old_time) const;

  MeanFilter() = default;

 private:
  std::size_t window_size_ = 0;
  std::size_t time_ = 0;
  double sum_ = 0.0;
  bool discard_max_min_ = false;

  double mean_ = 0.0;
  double stddev_ = 0.0;

  // front = earliest
  std::deque<std::pair<std::size_t, double>> values_;
  // front = min
  std::deque<std::pair<std::size_t, double>> min_candidates_;
  // front = max
  std::deque<std::pair<std::size_t, double>> max_candidates_;

 private:
  DISALLOW_COPY_AND_ASSIGN(MeanFilter);
};

}  // namespace util
}  // namespace math
}  // namespace iggy

#endif  // IGGY_MATH_UTIL_MEAN_FILTER_H_

