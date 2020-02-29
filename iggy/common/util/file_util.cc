// Copyright 2020 insaneyilin All Rights Reserved.
#include "iggy/common/util/file_util.h"

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <limits.h>
#include <stddef.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace iggy {
namespace common {
namespace util {

bool FileUtil::GetAbsolutePath(const std::string &path,
    std::string *abs_path) {
  return true;
}

bool FileUtil::GetBaseName(const std::string &path,
    std::string *basename) {
  return true;
}

bool FileUtil::GetDirName(const std::string &path,
    std::string *dirname) {
  return true;
}

bool FileUtil::Exists(const std::string &path) {
  return true;
}

int FileUtil::GetFileSize(const std::string &path) {
  return 0;
}

bool FileUtil::GetFileList(const std::string &path, const std::string &ext,
    std::vector<std::string> *filelist) {
  return true;
}

bool FileUtil::IsFile(const std::string &path) {
  return true;
}

bool IsDir(const std::string &path) {
  return true;
}

bool SplitBaseName(const std::string &path,
    std::pair<std::string, std::string> *result) {
  return true;
}

bool SplitExtension(const std::string &path,
    std::pair<std::string, std::string> *result) {
  return true;
}

}  // namespace util
}  // namespace common
}  // namespace iggy
