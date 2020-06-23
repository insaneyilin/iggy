// Copyright 2020 insaneyilin All Rights Reserved.
#include "iggy/image_proc/io/image.h"

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

Image::Image(const std::string &filename) {
}

bool Image::Read(const std::string &filename) {
  data_ = stbi_load(filename.c_str(),
      &width_, &height_, &channels_, 0);
  return true;
}

bool Image::Write(const std::string &filename) {
  return true;
}

}  // namespace io
}  // namespace image_proc
}  // namespace iggy
