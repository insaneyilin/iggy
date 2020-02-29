// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_COMMON_UTIL_STRING_UTIL_H_
#define IGGY_COMMON_UTIL_STRING_UTIL_H_

#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "iggy/common/util/macros.h"

namespace iggy {
namespace common {
namespace util {

class StringUtil {
 public:
  enum class TrimType {
    TRIM_TYPE_BOTH = 0,
    TRIM_TYPE_LEFT = 1,
    TRIM_TYPE_RIGHT = 2,
    TRIM_TYPE_COUNT = 3
  };

  static std::string TrimType2Str(TrimType type) {
    switch (type) {
      case TrimType::TRIM_TYPE_BOTH:
        return "TRIM_TYPE_BOTH";
      case TrimType::TRIM_TYPE_LEFT:
        return "TRIM_TYPE_LEFT";
      case TrimType::TRIM_TYPE_RIGHT:
        return "TRIM_TYPE_RIGHT";
      default:
        return "UNKNOW";
    }
  }

 public:
  template <typename T>
  static std::string ValueToStr(const T& val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
  }

  static void Split(const std::string &str, char delim,
      std::vector<std::string> *terms);

  static void Split(const std::string &str, const std::string &delim,
      std::vector<std::string> *terms);

  template <typename Iterator>
  static void Join(Iterator start, Iterator end, const std::string &delim,
      std::string *result) {
    *result = "";
    for (Iterator it = start; it != end; ++it) {
      if (it != start) {
        *result += delim;
      }
      *result += ValueToStr(*it);
    }
  }

  static std::string Trim(const std::string &str, TrimType type);
  static std::string Trim(const std::string &str);
  static std::string LeftTrim(const std::string &str);
  static std::string RightTrim(const std::string &str);

  static bool StartsWith(const std::string &str, const std::string &prefix) {
    return std::equal(prefix.begin(), prefix.end(), str.begin());
  }

  static bool EndsWith(const std::string &str, const std::string &suffix) {
    return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
  }

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(StringUtil);
};

}  // namespace util
}  // namespace common
}  // namespace iggy

#endif  // IGGY_COMMON_UTIL_STRING_UTIL_H_
