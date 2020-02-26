// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "iggy/common/util/string_util.h"

namespace iggy {
namespace common {
namespace util {

TEST(StringUtilTest, SplitTest) {
  std::string str1 = "2 3 5 7 11 13 17";
  std::vector<std::string> terms1;
  std::vector<std::string> gt_terms1 = {
    "2", "3", "5", "7", "11", "13", "17"
  };
  StringUtil::Split(str1, ' ', &terms1);
  EXPECT_THAT(terms1, ::testing::ContainerEq(gt_terms1));

  std::string str2 = "don't be evil";
  std::vector<std::string> terms2;
  std::vector<std::string> gt_terms2 = {
    "don", "t be evil"
  };
  StringUtil::Split(str2, '\'', &terms2);
  EXPECT_THAT(terms2, ::testing::ContainerEq(gt_terms2));

  std::string str3 = "hello;;this;;is;;a;;book";
  std::vector<std::string> terms3;
  std::vector<std::string> gt_terms3 = {
    "hello", "this", "is", "a", "book"
  };
  StringUtil::Split(str3, ";;", &terms3);
  EXPECT_THAT(terms3, ::testing::ContainerEq(gt_terms3));
}

TEST(StringUtilTest, TrimTest) {
  std::string str = "ahoy~~      ";
  EXPECT_EQ(StringUtil::Trim(str), std::string("ahoy~~"));
  EXPECT_EQ(StringUtil::RightTrim(str), std::string("ahoy~~"));

  str = "    lala  haha ...    ";
  EXPECT_EQ(StringUtil::Trim(str), std::string("lala  haha ..."));
  EXPECT_EQ(StringUtil::RightTrim(str), std::string("    lala  haha ..."));
  EXPECT_EQ(StringUtil::LeftTrim(str), std::string("lala  haha ...    "));
}

TEST(StringUtilTest, MiscTest) {
  std::string str = "abcdedf";
  EXPECT_TRUE(StringUtil::StartsWith(str, "a"));
  EXPECT_TRUE(StringUtil::StartsWith(str, "ab"));
  EXPECT_TRUE(StringUtil::StartsWith(str, "abc"));
  EXPECT_FALSE(StringUtil::StartsWith(str, " abc"));
  EXPECT_TRUE(StringUtil::EndsWith(str, "f"));
  EXPECT_TRUE(StringUtil::EndsWith(str, "df"));
  EXPECT_TRUE(StringUtil::EndsWith(str, "edf"));
  EXPECT_FALSE(StringUtil::EndsWith(str, "fde"));

  int a = 114514;
  EXPECT_EQ(StringUtil::ValueToStr(a), "114514");
  double flt = 3.14159;
  EXPECT_EQ(StringUtil::ValueToStr(flt), "3.14159");

  std::vector<int> nums1 = {1, 2, 3, 4, 5};
  std::string joined_str;
  StringUtil::Join(nums1.begin(), nums1.end(), ", ", &joined_str);
  EXPECT_EQ(joined_str, "1, 2, 3, 4, 5");
}

}  // namespace util
}  // namespace common
}  // namespace iggy
