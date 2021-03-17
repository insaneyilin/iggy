// Copyright 2020 insaneyilin All Rights Reserved.

#include "iggy/common/util/string_util.h"

#include <iostream>
#include <algorithm>

namespace iggy {
namespace common {
namespace util {

void StringUtil::Split(const std::string &str, char delim,
    std::vector<std::string> *terms) {
  terms->clear();
  std::stringstream ss(str);
  std::string segment;
  while (std::getline(ss, segment, delim)) {
    terms->push_back(segment);
  }
}

void StringUtil::Split(const std::string &str, const std::string &delim,
  std::vector<std::string> *terms) {
  terms->clear();
  std::string::size_type last_idx = str.find_first_not_of(delim, 0);
  std::string::size_type idx = str.find(delim, last_idx);

  while (std::string::npos != idx || std::string::npos != last_idx) {
    terms->push_back(str.substr(last_idx, idx - last_idx));
    last_idx = str.find_first_not_of(delim, idx);
    idx = str.find(delim, last_idx);
  }
}

using TrimType = StringUtil::TrimType;
std::string StringUtil::Trim(const std::string &str, TrimType type) {
  std::string res_str = str;
  switch (type) {
  case TrimType::TRIM_TYPE_LEFT:
    res_str.erase(
        res_str.begin(),
        std::find_if_not(res_str.begin(), res_str.end(),
            [](int ch) { return std::isspace(ch) != 0; }));
    break;
  case TrimType::TRIM_TYPE_RIGHT:
    res_str.erase(
        std::find_if_not(res_str.rbegin(), res_str.rend(),
            [](int ch) { return isspace(ch) != 0; }).base(),
        res_str.end());
    break;
  case TrimType::TRIM_TYPE_BOTH:
    res_str.erase(
        res_str.begin(),
        std::find_if_not(res_str.begin(), res_str.end(),
            [](int ch) { return std::isspace(ch) != 0; }));
    res_str.erase(
        std::find_if_not(res_str.rbegin(), res_str.rend(),
            [](int ch) { return isspace(ch) != 0; }).base(),
        res_str.end());
    break;
  default:
    std::cerr << "Invalid trim type: " << TrimType2Str(type) << std::endl;
    break;
  }
  return res_str;
}

std::string StringUtil::Trim(const std::string &str) {
  return Trim(str, TrimType::TRIM_TYPE_BOTH);
}

std::string StringUtil::LeftTrim(const std::string &str) {
  return Trim(str, TrimType::TRIM_TYPE_LEFT);
}

std::string StringUtil::RightTrim(const std::string &str) {
  return Trim(str, TrimType::TRIM_TYPE_RIGHT);
}

}  // namespace util
}  // namespace common
}  // namespace iggy
