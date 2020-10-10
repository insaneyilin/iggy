// Copyright 2020 insaneyilin All Rights Reserved.
#ifndef IGGY_IMAGE_PROC_BASE_RECT_H_
#define IGGY_IMAGE_PROC_BASE_RECT_H_

namespace iggy {
namespace image_proc {
namespace base {

template <typename T>
struct Rect {
  Rect() : x(0), y(0), width(0), height(0) {}
  Rect(T xx, T yy, T ww, T hh) :
      x(xx), y(yy), width(ww), height(hh) {}

  // top left (x, y) and (width, height)
  T x = 0;
  T y = 0;
  T width = 0;
  T height = 0;
};

typedef Rect<int> RectI;
typedef Rect<float> RectF;
typedef Rect<double> RectD;

}  // namespace base
}  // namespace image_proc
}  // namespace iggy

#endif  // IGGY_IMAGE_PROC_BASE_RECT_H_

