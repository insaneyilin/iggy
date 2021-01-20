// Copyright 2020 insaneyilin All Rights Reserved.

#include "iggy/math/util/mean_filter.h"

#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>

namespace iggy {
namespace math {
namespace util {

double MeanFilter::Update(double measurement) {
  const std::size_t double_window_size = 2 * window_size_;
  ++time_;
  time_ %= double_window_size;
  if (values_.size() == window_size_) {
    RemoveOldestValue();
  }
  Add(measurement);
  double min_val = 0.0;
  double max_val = 0.0;
  std::size_t min_time = 0;
  std::size_t max_time = 0;
  const std::size_t values_size = values_.size();
  if (discard_max_min_ && values_size > 2 && GetMaxMin(&max_val, &min_val,
      &max_time, &min_time)) {
    mean_ = (sum_ - min_val - max_val) / (values_size - 2);
    // Compute Stddev
    std::vector<double> diff;
    for (const auto &x : values_) {
      if (x.first == min_time) {
        continue;
      }
      if (x.first == max_time) {
        continue;
      }
      diff.push_back(x.second - mean_);
    }
    double sum_of_diff_sqrs = std::inner_product(
        diff.begin(), diff.end(), diff.begin(), 0.0);
    double variance = sum_of_diff_sqrs / (values_size - 2);
    stddev_ = std::sqrt(variance);
  } else {
    mean_ = sum_ / values_size;
    // Compute Stddev
    std::vector<double> diff(values_size);
    std::transform(values_.begin(), values_.end(), diff.begin(),
        [&](const std::pair<std::size_t, double> &x) {
      return x.second - mean_;
    });
    double sum_of_diff_sqrs = std::inner_product(
        diff.begin(), diff.end(), diff.begin(), 0.0);
    double variance = sum_of_diff_sqrs / values_size;
    stddev_ = std::sqrt(variance);
  }
  return mean_;
}

void MeanFilter::Add(double value) {
  values_.push_back(std::make_pair(time_, value));
  sum_ += value;
  while (min_candidates_.size() > 0 && min_candidates_.back().second > value) {
    min_candidates_.pop_back();
  }
  min_candidates_.push_back(std::make_pair(time_, value));
  while (max_candidates_.size() > 0 && max_candidates_.back().second < value) {
    max_candidates_.pop_back();
  }
  max_candidates_.push_back(std::make_pair(time_, value));
}

void MeanFilter::RemoveOldestValue() {
  double oldest_value = values_.front().second;
  values_.pop_front();
  sum_ -= oldest_value;
  if (ShouldPopOldestCandidate(min_candidates_.front().first)) {
    min_candidates_.pop_front();
  }
  if (ShouldPopOldestCandidate(max_candidates_.front().first)) {
    max_candidates_.pop_front();
  }
}

bool MeanFilter::GetMaxMin(double *max_val, double *min_val,
    std::size_t *max_time, std::size_t *min_time) const {
  if (max_candidates_.empty() || min_candidates_.empty()) {
    return false;
  }
  *max_val = max_candidates_.front().second;
  *min_val = min_candidates_.front().second;
  *max_time = max_candidates_.front().first;
  *min_time = min_candidates_.front().first;
  return true;
}

bool MeanFilter::ShouldPopOldestCandidate(const std::size_t old_time) const {
  if (old_time < window_size_) {
    return old_time + window_size_ == time_;
  } else if (time_ < window_size_) {
    return old_time == time_ + window_size_;
  }
  return false;
}

}  // namespace util
}  // namespace math
}  // namespace iggy

