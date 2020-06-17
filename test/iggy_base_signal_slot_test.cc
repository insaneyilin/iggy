// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "iggy/base/signal_slot.h"

namespace iggy {
namespace base {

TEST(SignalSlotTest, ZeroParamSlot) {
  int n = 0;
  // connected by default
  Slot<> slot1([&]() {
    n = 1;
  });
  EXPECT_TRUE(slot1.connected());

  slot1();
  EXPECT_EQ(n, 1);

  slot1.Disconnect();
  EXPECT_FALSE(slot1.connected());

  // slot1 won't work if it is disconnected
  n = 0;
  slot1();
  EXPECT_NE(n, 1);

  // not connected when created
  Slot<> slot2([&]() {
    n = 2;
  }, false);
  EXPECT_FALSE(slot2.connected());

  n = 0;
  slot2();
  EXPECT_NE(n, 2);

  Slot<> slot3(nullptr);
  EXPECT_NO_FATAL_FAILURE(slot3());
}

TEST(SignalSlotTest, MultiParamsSlot) {
  int res = 0;
  Slot<int, int> slot_sum_of_two([&](int a, int b) {
    res = a + b;
  });
  EXPECT_TRUE(slot_sum_of_two.connected());

  slot_sum_of_two(1, 2);
  EXPECT_EQ(res, 3);

  slot_sum_of_two.Disconnect();
  EXPECT_FALSE(slot_sum_of_two.connected());

  res = 0;
  slot_sum_of_two(1, 2);
  EXPECT_NE(res, 3);
}

TEST(SignalSlotTest, NullSignalConnection) {
  Connection<> conn1;
  EXPECT_FALSE(conn1.IsConnected());
  EXPECT_FALSE(conn1.Disconnect());
  EXPECT_FALSE(conn1.HasSlot(nullptr));

  auto empty_slot = std::make_shared<Slot<>>([]() {});
  Connection<> conn2(empty_slot, nullptr);
  EXPECT_TRUE(conn2.IsConnected());
  EXPECT_FALSE(conn2.Disconnect());
  EXPECT_TRUE(conn2.HasSlot(empty_slot));

  EXPECT_FALSE(conn1.HasSlot(empty_slot));

  conn2 = conn2;
  conn1 = conn2;
  EXPECT_TRUE(conn1.IsConnected());
  EXPECT_FALSE(conn1.Disconnect());
  EXPECT_TRUE(conn1.HasSlot(empty_slot));

  Signal<> sig;
  Connection<> conn3(nullptr, &sig);
  EXPECT_FALSE(conn3.Disconnect());
}

TEST(SignalSlotTest, MultiConnections) {
  Signal<int, int> sig;
  int sum = 0;
  int prod = 0;

  auto conn1 = sig.Connect([&sum](int a, int b) {
    sum = a + b;
  });
  auto conn2 = sig.Connect([&prod](int a, int b) {
    prod = a * b;
  });

  int a = 1;
  int b = 2;
  sig(a, b);
  EXPECT_EQ(sum, a + b);
  EXPECT_EQ(prod, a * b);

  Connection<int, int> conn3;
  EXPECT_FALSE(sig.Disconnect(conn3));
  EXPECT_TRUE(sig.Disconnect(conn2));
  sum = 0;
  prod = 0;
  a = 3;
  b = 4;
  sig(a, b);
  EXPECT_EQ(sum, a + b);
  EXPECT_NE(prod, a * b);

  sig.DisconnectAllSlots();
  sum = 0;
  prod = 0;
  a = 5;
  b = 6;
  sig(a, b);
  EXPECT_NE(sum, a + b);
  EXPECT_NE(prod, a * b);
}

}  // namespace base
}  // namespace iggy

