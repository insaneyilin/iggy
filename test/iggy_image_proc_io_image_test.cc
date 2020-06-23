// Copyright 2020 insaneyilin All Rights Reserved.

#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "iggy/image_proc/io/image.h"

namespace iggy {
namespace image_proc {
namespace io {

TEST(ImageProcIOImage, LoadImage) {
  std::string filename("lena512color.png");
  Image image;
  EXPECT_TRUE(image.Read(filename));
  EXPECT_EQ(image.width(), 512);
  EXPECT_EQ(image.height(), 512);
}

}  // namespace io
}  // namespace image_proc
}  // namespace iggy
