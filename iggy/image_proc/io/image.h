// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_IMAGE_PROC_IO_IMAGE_H_
#define IGGY_IMAGE_PROC_IO_IMAGE_H_

#include <vector>
#include <memory>
#include <string>

namespace iggy {
namespace image_proc {
namespace io {

class Image {
 public:
  Image();
  ~Image();
  explicit Image(const std::string &filename);

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

  int channels() const {
    return channels_;
  }

  const unsigned char* data() const {
    return data_;
  }

  unsigned char* mutable_data() {
    return data_;
  }

  bool Read(const std::string &filename);
  bool Write(const std::string &filename);

  bool Clear(unsigned int value);

 private:
  unsigned char* data_ = nullptr;
  int width_ = 0;
  int height_ = 0;
  int channels_ = 0;
  int desired_channels_ = 0;
};

}  // namespace io
}  // namespace image_proc
}  // namespace iggy

#endif  // IGGY_IMAGE_PROC_IO_IMAGE_H_
