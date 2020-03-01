// Copyright 2020 insaneyilin All Rights Reserved.
#include "iggy/common/util/file_util.h"

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

#include "iggy/common/util/string_util.h"

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
  *basename = "";
  if (!FileUtil::Exists(path)) {
    return false;
  }
  std::string abs_path("");
  if (!FileUtil::GetAbsolutePath(path, &abs_path)) {
    return false;
  }
  std::string::size_type start = abs_path.rfind('/');
  if (start == std::string::npos) {
    start = 0;
  } else {
    // move to the next char after '/'.
    ++start;
  }
  std::string::size_type end = std::string::npos;
  const auto len = (end != std::string::npos) ? end - start : end;
  *basename = abs_path.substr(start, len);
  return true;
}

bool FileUtil::GetDirName(const std::string &path,
    std::string *dirname) {
  if (!FileUtil::Exists(path)) {
    return false;
  }
  std::string abs_path("");
  if (!FileUtil::GetAbsolutePath(path, &abs_path)) {
    return false;
  }
  std::string::size_type start = abs_path.rfind('/');
  if (start == std::string::npos) {
    start = 0;
  }
  *dirname = abs_path.substr(0, start);
  return true;
}

bool FileUtil::Exists(const std::string &path) {
  struct stat info;
  return stat(path.c_str(), &info) == 0;
}

int64_t FileUtil::GetFileSize(const std::string &path) {
  if (!FileUtil::Exists(path)) {
    return -1;
  }
  FILE *pfile = nullptr;
  int64_t fsize = 0;
  pfile = fopen(path.c_str(), "rb");
  if (!pfile) {
    return -1;
  }
  fseek(pfile, 0, SEEK_END);
  fsize = ftell(pfile);
  fclose(pfile);
  return fsize;
}

bool FileUtil::GetFileContent(const std::string &path, std::string *content) {
  if (!FileUtil::Exists(path)) {
    return false;
  }
  std::ifstream fin(path);
  if (!fin) {
    return false;
  }
  std::stringstream ss;
  ss << fin.rdbuf();
  *content = ss.str();
  return true;
}

bool FileUtil::GetFileList(const std::string &path, const std::string &ext,
    std::vector<std::string> *filelist) {
  if (!FileUtil::Exists(path)) {
    return false;
  }
  if (!FileUtil::IsDir(path)) {
    return false;
  }

  filelist->clear();
  DIR *directory = opendir(path.c_str());
  if (!directory) {
    return false;
  }
  struct dirent *entry;
  while ((entry = readdir(directory)) != nullptr) {
    // skip "." and "..".
    if (strcmp(entry->d_name, ".") == 0 ||
        strcmp(entry->d_name, "..") == 0) {
      continue;
    }
    if (entry->d_type != DT_REG) {
      continue;
    }
    std::string fname(entry->d_name);
    if (StringUtil::EndsWith(fname, ext)) {
      filelist->push_back(fname);
    }
  }
  closedir(directory);
  return true;
}

bool FileUtil::IsDir(const std::string &path) {
  struct stat info;
  return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
}

// TODO(yilin)
bool FileUtil::SplitBaseName(const std::string &path,
    std::pair<std::string, std::string> *result) {
  if (!FileUtil::Exists(path)) {
    return false;
  }

  std::string::size_type start = path.rfind('/');
  if (start == std::string::npos) {
    start = 0;
  } else {
    // move to the next char after '/'.
    ++start;
  }
  std::string::size_type end = std::string::npos;
  const auto len = (end != std::string::npos) ? end - start : end;
  result->first = path.substr(0, start - 1);
  result->second = path.substr(start, len);
  return true;
}

}  // namespace util
}  // namespace common
}  // namespace iggy
