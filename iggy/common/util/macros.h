// Copyright 2020 insaneyilin All Rights Reserved.

#ifndef IGGY_COMMON_UTIL_MACROS_H_
#define IGGY_COMMON_UTIL_MACROS_H_

namespace iggy {
namespace common {
namespace util {

#undef DISALLOW_COPY
#define DISALLOW_COPY(classname)                                          \
  classname(const classname&) = delete

#undef DISALLOW_ASSIGN
#define DISALLOW_ASSIGN(classname)                                        \
  classname& operator=(const classname&) = delete

#undef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(classname)                               \
  classname(const classname&) = delete;                                   \
  classname& operator=(const classname&) = delete;

#undef DISALLOW_IMPLICIT_CONSTRUCTORS
#define DISALLOW_IMPLICIT_CONSTRUCTORS(classname)                         \
  classname() = delete;                                                   \
  DISALLOW_COPY_AND_ASSIGN(classname)

#undef DISALLOW_MOVE
#define DISALLOW_MOVE(classname)                                          \
  classname(classname&&) = delete;                                        \
  classname& operator=(classname &&) = delete;

#undef DECLARE_SINGLETON
#define DECLARE_SINGLETON(classname)                                      \
 public:                                                                  \
  static classname *Instance() {                                          \
    static classname instance;                                            \
    return &instance;                                                     \
  }                                                                       \
 private:                                                                 \
  classname();                                                            \
  DISALLOW_COPY_AND_ASSIGN(classname);                                    \
  DISALLOW_MOVE(classname)

}  // namespace util
}  // namespace common
}  // namespace iggy

#endif  // IGGY_COMMON_UTIL_MACROS_H_
