// Copyright 2020 insaneyilin All Rights Reserved.

#include "iggy/image_proc/image_transform/image_transform.h"

#include <algorithm>

#include "iggy/math/util/math_util.h"

namespace iggy {
namespace image_proc {
namespace image_transform {

void ImageTransForm::Rotate(const base::Image &in_image, float degrees,
                            base::Image *out_image) {
  out_image->CopyFrom(in_image);
  out_image->Clear(255);

  float radians = math::util::MathUtil::Deg2Rad(degrees);
  // Compute the cosine and sine only once
  float cosine = std::cos(radians);
  float sine = std::sin(radians);

  // Compute the dimensions of the result image
  // First get the coordinates of the 3 corners other than
  // origin
  const int image_height = in_image.height();
  const int image_width = in_image.width();
  int x1 = static_cast<int>(-image_height * sine);
  int y1 = static_cast<int>(image_height * cosine);
  int x2 = static_cast<int>(image_width * cosine - image_height * sine);
  int y2 = static_cast<int>(image_height * cosine + image_width * sine);
  int x3 = static_cast<int>(image_width * cosine);
  int y3 = static_cast<int>(image_width * sine);

  int minx = std::min(0, std::min(x1, std::min(x2, x3)));
  int miny = std::min(0, std::min(y1, std::min(y2, y3)));
  int maxx = std::max(x1, std::max(x2, x3));
  int maxy = std::max(y1, std::max(y2, y3));

  int w = maxx - minx;
  int h = maxy - miny;

  // Now do the actual rotating - a pixel at a time
  // Use reverse mapping to avoid 'holes'
  // i.e. compute the source point for each destination point
  unsigned int r = 0;
  unsigned int g = 0;
  unsigned int b = 0;
  unsigned int a = 0;
  for (int y = miny; y < maxy; ++y) {
    for (int x = minx; x < maxx; ++x) {
      int src_x = static_cast<int>(x * cosine + y * sine);
      int src_y = static_cast<int>(y * cosine - x * sine);
      if (src_x < 0 || src_x >= image_width || src_y < 0 ||
          src_y >= image_height) {
        continue;
      }
      // NOTE: do not forget to check dest (x, y)!!!
      if (x < 0 || x >= image_width || y < 0 || y >= image_height) {
        continue;
      }
      in_image.GetPixel(src_x, src_y, &r, &g, &b, &a);
      out_image->SetPixel(x, y, r, g, b, a);
    }
  }
}

}  // namespace image_transform
}  // namespace image_proc
}  // namespace iggy
