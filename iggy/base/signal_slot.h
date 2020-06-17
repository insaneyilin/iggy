// Copyright 2020 insaneyilin All Rights Reserved.
// Reference: cyber/base/signal.h from ApolloAuto

#ifndef IGGY_BASE_SIGNAL_SLOT_H_
#define IGGY_BASE_SIGNAL_SLOT_H_

#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <mutex>  // NOLINT

#include "iggy/common/util/macros.h"

namespace iggy {
namespace base {

template <typename... Args>
class Slot;

template <typename... Args>
class Connection;

template <typename... Args>
class Signal {
 public:
  using Callback = std::function<void(Args...)>;
  using SlotPtr = std::shared_ptr<Slot<Args...>>;
  using SlotList = std::list<SlotPtr>;
  using ConnectionType = Connection<Args...>;

  Signal() = default;
  virtual ~Signal() {
    DisconnectAllSlots();
  }

  void operator()(Args... args) {
    // considering concurrency performance of slots, we first
    // copy a local slots list
    SlotList local_slots;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      for (auto &slot : slots_) {
        local_slots.emplace_back(slot);
      }
    }
    if (!local_slots.empty()) {
      for (auto &slot : local_slots) {
        (*slot)(args...);
      }
    }
    ClearDisconnectedSlots();
  }

  ConnectionType Connect(const Callback& cb) {
    auto slot = std::make_shared<Slot<Args...>>(cb);
    {
      std::lock_guard<std::mutex> lock(mutex_);
      slots_.emplace_back(slot);
    }
    return ConnectionType(slot, this);
  }

  bool Disconnect(const ConnectionType& conn) {
    bool found = false;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      for (auto &slot : slots_) {
        if (conn.HasSlot(slot)) {
          found = true;
          slot->Disconnect();
        }
      }
    }
    if (found) {
      ClearDisconnectedSlots();
    }
    return found;
  }

  void DisconnectAllSlots() {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto &slot : slots_) {
      slot->Disconnect();
    }
    slots_.clear();
  }

 private:
  void ClearDisconnectedSlots() {
    std::lock_guard<std::mutex> lock(mutex_);
    slots_.erase(
        std::remove_if(slots_.begin(), slots_.end(),
                       [](const SlotPtr &slot) {
                           return !slot->connected();
                       }),
                       slots_.end());
  }

 private:
  SlotList slots_;
  std::mutex mutex_;

 private:
  DISALLOW_COPY_AND_ASSIGN(Signal);
};

template <typename... Args>
class Connection {
 public:
  using SlotPtr = std::shared_ptr<Slot<Args...>>;
  using SignalPtr = Signal<Args...>*;

  Connection() : slot_(nullptr), signal_(nullptr) {}
  Connection(const SlotPtr &slot, const SignalPtr &signal)
      : slot_(slot), signal_(signal) {}
  virtual ~Connection() {
    slot_ = nullptr;
    signal_ = nullptr;
  }

  Connection& operator=(const Connection &that) {
    if (this != &that) {
      this->slot_ = that.slot_;
      this->signal_ = that.signal_;
    }
    return *this;
  }

  bool HasSlot(const SlotPtr &slot) const {
    if (slot != nullptr && slot_ != nullptr) {
      return slot_.get() == slot.get();
    }
    return false;
  }

  bool IsConnected() const {
    if (slot_) {
      return slot_->connected();
    }
    return false;
  }

  bool Disconnect() {
    if (signal_ && slot_) {
      return signal_->Disconnect(*this);
    }
    return false;
  }

 private:
  SlotPtr slot_;
  SignalPtr signal_;
};

template <typename... Args>
class Slot {
 public:
  using Callback = std::function<void(Args...)>;

  Slot(const Slot& that)
      : cb_(that.cb_), connected_(that.connected_) {}
  explicit Slot(const Callback& cb, bool connected = true)
      : cb_(cb), connected_(connected) {}
  virtual ~Slot() {}

  void operator()(Args... args) {
    if (connected_ && cb_) {
      cb_(args...);
    }
  }

  void Disconnect() {
    connected_ = false;
  }

  bool connected() const {
    return connected_;
  }

 private:
  Callback cb_;
  bool connected_ = true;
};

}  // namespace base
}  // namespace iggy

#endif  // IGGY_BASE_SIGNAL_SLOT_H_

