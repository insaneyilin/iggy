// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_COMMON_UTIL_FILE_UTIL_H_
#define IGGY_COMMON_UTIL_FILE_UTIL_H_

#include <functional>
#include <string>
#include <vector>
#include <utility>

#include "iggy/common/util/macros.h"

namespace iggy {
namespace common {
namespace util {

class FileUtil {
 public:
  enum class FileType {
    FILE_TYPE_FILE = 0,
    FILE_TYPE_DIR = 1,
    FILE_TYPE_COUNT = 2
  };
  static std::string FileType2Str(FileType type) {
    switch (type) {
      case FileType::FILE_TYPE_FILE:
        return "FILE_TYPE_FILE";
      case FileType::FILE_TYPE_DIR:
        return "FILE_TYPE_DIR";
      default:
        return "UNKNOW";
    }
  }

 public:
  static bool GetAbsolutePath(const std::string &path, std::string *abs_path);
  static bool GetBaseName(const std::string &path, std::string *basename);
  static bool GetDirName(const std::string &path, std::string *dirname);
  static bool Exists(const std::string &path);

  // get file size in bytes
  static int64_t GetFileSize(const std::string &path);
  static bool GetFileContent(const std::string &path, std::string *content);
  static bool GetFileList(const std::string &path, const std::string &ext,
      std::vector<std::string> *filelist);
  static bool IsDir(const std::string &path);

  static bool SplitBaseName(const std::string &path,
      std::pair<std::string, std::string> *result);

  template <typename... Args>
  static bool Walk(const std::string &path,
      std::function<bool(Args &&...)> visit, Args &&... args);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(FileUtil);
};

template <typename... Args>
bool FileUtil::Walk(const std::string &path,
    std::function<bool(Args &&...)> visit, Args &&... args) {
  return true;
}

}  // namespace util
}  // namespace common
}  // namespace iggy

#endif  // IGGY_COMMON_UTIL_FILE_UTIL_H_
