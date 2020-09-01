// Copyright 2020 insaneyilin All Rights Reserved.
#include "iggy/image_proc/io/image.h"

#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>

#include "iggy/common/util/string_util.h"

// stb_image
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#ifndef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#endif

#include "third_party/stb_image/stb_image.h"
#include "third_party/stb_image/stb_image_write.h"
#include "third_party/stb_image/stb_image_resize.h"

namespace iggy {
namespace image_proc {
namespace io {

Image::Image() {
}

Image::~Image() {
  if (data_) {
    stbi_image_free(data_);
  }
}

Image::Image(int width, int height, int channels) {
  width_ = width;
  height_ = height;
  channels_ = channels;
  data_ = new unsigned char[width_ * height_ * channels_];
}

Image::Image(const std::string &filename) {
  if (!Read(filename)) {
    throw std::invalid_argument("invalid image filename");
  }
}

bool Image::Read(const std::string &filename) {
  data_ = stbi_load(filename.c_str(),
      &width_, &height_, &channels_, 0);
  if (data_ == nullptr) {
    std::cerr << "failed to read image: " << filename << '\n';
    return false;
  }
  return true;
}

bool Image::Write(const std::string &filename) {
  using ::iggy::common::util::StringUtil;
  if (StringUtil::EndsWith(filename, ".png")) {
    stbi_write_png(filename.c_str(), static_cast<int>(width()),
        static_cast<int>(height()), static_cast<int>(channels()),
        (const stbi_uc*)data_, 0);
  } else if (StringUtil::EndsWith(filename, ".bmp")) {
    stbi_write_bmp(filename.c_str(), static_cast<int>(width()),
        static_cast<int>(height()), static_cast<int>(channels()),
        (const stbi_uc*)data_);
  } else if (StringUtil::EndsWith(filename, ".tga")) {
    stbi_write_tga(filename.c_str(), static_cast<int>(width()),
        static_cast<int>(height()), static_cast<int>(channels()),
        (const stbi_uc*)data_);
  } else if (StringUtil::EndsWith(filename, ".jpg")) {
    stbi_write_jpg(filename.c_str(), static_cast<int>(width()),
        static_cast<int>(height()), static_cast<int>(channels()),
        (const stbi_uc*)data_, 80);
  } else {
    std::cerr << "unsupported image format: " << filename << '\n';
    return false;
  }
  return true;
}

bool Image::Clear(unsigned int value) {
  if (!data_) {
    return false;
  }
  std::memset(data_, value, width_ * height_ * channels_);
  return true;
}

bool Image::Clear(unsigned int r, unsigned int g, unsigned int b,
    unsigned int a) {
  if (!data_) {
    return false;
  }
  if (channels_ != 1 && channels_ != 3 && channels_ != 4) {
    return false;
  }
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      const int offset = channels_ * (width_ * i + j);
      if (channels_ == 1) {
        data_[offset] = r;
      } else if (channels_ == 3) {
        data_[offset] = r;
        data_[offset + 1] = g;
        data_[offset + 2] = b;
      } else if (channels_ == 4) {
        data_[offset] = r;
        data_[offset + 1] = g;
        data_[offset + 2] = b;
        data_[offset + 3] = a;
      }
    }
  }

  return true;
}

}  // namespace io
}  // namespace image_proc
}  // namespace iggy
