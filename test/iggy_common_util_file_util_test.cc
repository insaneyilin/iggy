// Copyright 2020 insaneyilin All Rights Reserved.

#include <stdarg.h>

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "iggy/common/util/file_util.h"

namespace iggy {
namespace common {
namespace util {

TEST(FileUtil, TestExists) {
  EXPECT_TRUE(FileUtil::Exists("."));
  EXPECT_TRUE(FileUtil::Exists(".."));
  EXPECT_FALSE(FileUtil::Exists(".!@#%$^#non-exist"));
}

TEST(FileUtil, TestEnsureDirectory) {
  EXPECT_TRUE(FileUtil::EnsureDirectory("."));
  EXPECT_TRUE(FileUtil::EnsureDirectory(".."));
  EXPECT_TRUE(FileUtil::EnsureDirectory("test_dir_for_ensure_dir"));
}

TEST(FileUtil, TestGetAbsPath) {
  std::string abs_path("");
  EXPECT_TRUE(FileUtil::GetAbsolutePath(".", &abs_path));
  EXPECT_NE(abs_path, "");
  std::cout << "abs_path: " << abs_path << '\n';
}

TEST(FileUtil, TestGetBaseName) {
  std::string basename("");
  EXPECT_TRUE(FileUtil::GetBaseName(".", &basename));
  EXPECT_NE(basename, "");
  std::cout << "basename: " << basename << '\n';
}

TEST(FileUtil, TestGetDirName) {
  std::string dirname("");
  EXPECT_TRUE(FileUtil::GetDirName(".", &dirname));
  EXPECT_NE(dirname, "");
  std::cout << "dirname: " << dirname << '\n';
}

TEST(FileUtil, TestGetFileContentAndSize) {
  std::string content("");
  EXPECT_EQ(FileUtil::GetFileSize(".!@$#%@^"), -1);
  EXPECT_FALSE(FileUtil::GetFileContent(".!@$#%@^", &content));
}

// TODO(yilin): add more tests

}  // namespace util
}  // namespace common
}  // namespace iggy
