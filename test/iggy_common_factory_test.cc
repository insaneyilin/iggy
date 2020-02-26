// Copyright 2020 insaneyilin All Rights Reserved.

#include <cmath>
#include <string>

#include "gtest/gtest.h"

#include "iggy/common/factory/autoreg_factory.h"

namespace iggy {
namespace common {
namespace factory {

// Base Class
class Vehicle {
 public:
  Vehicle() = default;
  ~Vehicle() = default;
  virtual std::string Name() const {
    return "Vehicle";
  }
};
REGISTER_BASE_CLASS_FACTORY(Vehicle);
#define REGISTER_VEHICLE_BY_NAME(sub_class_name) \
  REGISTER_SUB_CLASS_BY_NAME(Vehicle, sub_class_name)

// Derived Classes
class Car : Vehicle {
 public:
  Car() = default;
  ~Car() = default;
  std::string Name() const override {
    return "Car";
  }
};
REGISTER_VEHICLE_BY_NAME(Car);

class Van : Vehicle {
 public:
  Van() = default;
  ~Van() = default;
  std::string Name() const override {
    return "Van";
  }
};
REGISTER_VEHICLE_BY_NAME(Van);

class Truck : Vehicle {
 public:
  Truck() = default;
  ~Truck() = default;
  std::string Name() const override {
    return "Truck";
  }
};
REGISTER_VEHICLE_BY_NAME(Truck);

TEST(FactoryTest, AutoRegisteringFactory) {
  Vehicle *veh = nullptr;
  veh = VehicleFactory::GetInstancePtrByName("Truck");
  EXPECT_TRUE(veh != nullptr);
  EXPECT_EQ(veh->Name(), "Truck");
  delete veh;
  veh = nullptr;

  veh = VehicleFactory::GetInstancePtrByName("Car");
  EXPECT_TRUE(veh != nullptr);
  EXPECT_EQ(veh->Name(), "Car");
  delete veh;
  veh = nullptr;

  veh = VehicleFactory::GetInstancePtrByName("Van");
  EXPECT_TRUE(veh != nullptr);
  EXPECT_EQ(veh->Name(), "Van");
  delete veh;
  veh = nullptr;

  veh = VehicleFactory::GetInstancePtrByName("Flying Car");
  EXPECT_TRUE(veh == nullptr);
}

}  // namespace factory
}  // namespace common
}  // namespace iggy
