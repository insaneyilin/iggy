// Copyright 2020 insaneyilin All Rights Reserved.

#ifndef IGGY_COMMON_UTIL_ANY_H_
#define IGGY_COMMON_UTIL_ANY_H_

namespace iggy {
namespace common {
namespace util {

class Any {
 public:
  Any() : holder_(nullptr) {}

  template <typename ValueType>
  explicit Any(const ValueType &value) : holder_(
      new PlaceHolder<ValueType>(value)) {}

  Any(const Any &that) : holder_(
      that.holder_ ? that.holder_->Clone() : nullptr) {}

  ~Any() {
    delete holder_;
  }

  template <typename ValueType>
  ValueType* AnyCast() {
    return holder_ ?
      &(static_cast<PlaceHolder<ValueType>*>(holder_)->value_) : nullptr;
  }

 private:
  /// PlaceHolder interface
  class IHolder {
   public:
    virtual ~IHolder() {}
    virtual IHolder* Clone() const = 0;
  };

  /// PlaceHolder
  template <typename ValueType>
  class PlaceHolder : public IHolder {
   public:
    explicit PlaceHolder(const ValueType &value) : value_(value) {}
    virtual ~PlaceHolder() {}
    IHolder* Clone() const override {
      return new PlaceHolder(value_);
    }

   public:
    ValueType value_;
  };

 private:
  IHolder *holder_;
};

}  // namespace util
}  // namespace common
}  // namespace iggy

#endif  // IGGY_COMMON_UTIL_ANY_H_
