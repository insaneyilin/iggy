// Copyright 2020 insaneyilin All Rights Reserved.

#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "iggy/image_proc/base/image.h"
#include "iggy/image_proc/image_transform/image_transform.h"

namespace iggy {
namespace image_proc {
namespace base {

TEST(ImageProcIOImage, LoadImage) {
  std::string filename("lena512color.png");
  Image image;
  EXPECT_TRUE(image.Read(filename));
  EXPECT_EQ(image.width(), 512);
  EXPECT_EQ(image.height(), 512);
  EXPECT_EQ(image.channels(), 4);

  Image copy;
  copy.CopyFrom(image);
  copy.Write("copy.png");

  EXPECT_TRUE(image.Clear(255));
  image.Write("test.png");
  image.Write("test.bmp");
  image.Write("test.jpg");
  image.Write("test.tga");
}

TEST(ImageProcIOImage, CreateImage) {
  Image image(1920, 1080, 3);
  EXPECT_EQ(image.width(), 1920);
  EXPECT_EQ(image.height(), 1080);
  EXPECT_EQ(image.channels(), 3);
  EXPECT_TRUE(image.Clear(255));
  image.Write("all_white.png");
  image.Write("all_white.bmp");
  image.Write("all_white.jpg");
  image.Write("all_white.tga");

  EXPECT_TRUE(image.Clear(0));
  image.Write("all_black.png");
  image.Write("all_black.bmp");
  image.Write("all_black.jpg");
  image.Write("all_black.tga");

  EXPECT_TRUE(image.Clear(255, 0, 0, 0));
  image.Write("all_red.png");
  image.Write("all_red.bmp");
  image.Write("all_red.jpg");
  image.Write("all_red.tga");

  EXPECT_TRUE(image.Clear(0, 255, 0, 0));
  image.Write("all_green.png");
  image.Write("all_green.bmp");
  image.Write("all_green.jpg");
  image.Write("all_green.tga");

  EXPECT_TRUE(image.Clear(0, 0, 255, 0));
  image.Write("all_blue.png");
  image.Write("all_blue.bmp");
  image.Write("all_blue.jpg");
  image.Write("all_blue.tga");
}

TEST(ImageProcIOImage, LoadInvalidImage) {
  {
    std::string filename("non-exists.png");
    Image image;
    EXPECT_FALSE(image.Read(filename));
  }
  {
    std::string filename("non-exists.gif");
    Image image;
    EXPECT_FALSE(image.Read(filename));
  }
}

TEST(ImageProcIOImage, SetAndGetPixel) {
  std::string filename("lena512color.png");
  Image image;
  EXPECT_TRUE(image.Read(filename));
  EXPECT_EQ(image.width(), 512);
  EXPECT_EQ(image.height(), 512);
  EXPECT_EQ(image.channels(), 4);
  unsigned int r = 0;
  unsigned int g = 0;
  unsigned int b = 0;
  unsigned int a = 0;
  for (int i = 100; i < 200; ++i) {
    for (int j = 100; j < 200; ++j) {
      image.SetPixel(j, i, 255, 255, 255, 255);
      image.GetPixel(j, i, &r, &g, &b, &a);
      EXPECT_EQ(r, 255);
      EXPECT_EQ(g, 255);
      EXPECT_EQ(b, 255);
      EXPECT_EQ(a, 255);
    }
  }
  image.Write("lena512color_set_pixel.png");
}

TEST(ImageProcIOImage, Rotate) {
  std::string filename("lena512color.png");
  Image image;
  EXPECT_TRUE(image.Read(filename));
  EXPECT_EQ(image.width(), 512);
  EXPECT_EQ(image.height(), 512);
  EXPECT_EQ(image.channels(), 4);

  Image rotated;
  image_transform::ImageTransForm::Rotate(image, 30.f, &rotated);
  rotated.Write("rotated_30_degrees.png");

  image_transform::ImageTransForm::Rotate(image, 10.f, &rotated);
  rotated.Write("rotated_10_degrees.png");
}

}  // namespace base
}  // namespace image_proc
}  // namespace iggy
