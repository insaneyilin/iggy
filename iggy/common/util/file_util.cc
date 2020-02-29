// Copyright 2020 insaneyilin All Rights Reserved.
#include "iggy/common/util/file_util.h"

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace iggy {
namespace common {
namespace util {

bool FileUtil::GetAbsolutePath(const std::string &path,
    std::string *abs_path) {
  if (!FileUtil::Exists(path)) {
    return false;
  }
  static const int kMaxPathLen = 10000;
  char c_abs_path[kMaxPathLen + 1];
  *abs_path = std::string(realpath(path.c_str(), c_abs_path));
  return true;
}

bool FileUtil::GetBaseName(const std::string &path,
    std::string *basename) {
  if (!FileUtil::Exists(path)) {
    return false;
  }
  return true;
}

bool FileUtil::GetDirName(const std::string &path,
    std::string *dirname) {
  if (!FileUtil::Exists(path)) {
    return false;
  }
  return true;
}

bool FileUtil::Exists(const std::string &path) {
  struct stat info;
  return stat(path.c_str(), &info) == 0;
}

int FileUtil::GetFileSize(const std::string &path) {
  if (!FileUtil::Exists(path)) {
    return -1;
  }
  return 0;
}

bool FileUtil::GetFileList(const std::string &path, const std::string &ext,
    std::vector<std::string> *filelist) {
  if (!FileUtil::Exists(path)) {
    return false;
  }
  return true;
}

bool IsDir(const std::string &path) {
  struct stat info;
  return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
}

bool SplitBaseName(const std::string &path,
    std::pair<std::string, std::string> *result) {
  if (!FileUtil::Exists(path)) {
    return false;
  }
  return true;
}

bool SplitExtension(const std::string &path,
    std::pair<std::string, std::string> *result) {
  if (!FileUtil::Exists(path)) {
    return false;
  }
  return true;
}

}  // namespace util
}  // namespace common
}  // namespace iggy
