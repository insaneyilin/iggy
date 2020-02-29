// Copyright 2020 insaneyilin All Rights Reserved.

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

TEST(FileUtil, TestGetAbsPath) {
  std::string abs_path("");
  EXPECT_TRUE(FileUtil::GetAbsolutePath(".", &abs_path));
  EXPECT_NE(abs_path, "");
  std::cout << "abs_path: " << abs_path << '\n';
}

// TODO(yilin): add more tests

}  // namespace util
}  // namespace common
}  // namespace iggy
