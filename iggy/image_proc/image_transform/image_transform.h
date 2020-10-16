// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_IMAGE_PROC_IMAGE_TRANSFORM_IMAGE_TRANSFORM_H_
#define IGGY_IMAGE_PROC_IMAGE_TRANSFORM_IMAGE_TRANSFORM_H_

#include "iggy/common/util/macros.h"
#include "iggy/image_proc/base/image.h"
#include "iggy/image_proc/base/rect.h"

namespace iggy {
namespace image_proc {
namespace image_transform {

class ImageTransForm {
 public:
  static void Rotate(const base::Image &in_image,
                     float degrees, base::Image *out_image);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(ImageTransForm);
};

}  // namespace image_transform
}  // namespace image_proc
}  // namespace iggy

#endif  // IGGY_IMAGE_PROC_IMAGE_TRANSFORM_IMAGE_TRANSFORM_H_
