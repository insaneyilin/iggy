// Copyright 2020 insaneyilin All Rights Reserved.

#ifndef IGGY_COMMON_FACTORY_AUTOREG_FACTORY_H_
#define IGGY_COMMON_FACTORY_AUTOREG_FACTORY_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "iggy/common/util/macros.h"
#include "iggy/common/util/any.h"

namespace iggy {
namespace common {
namespace factory {

class ObjectFactory {
 public:
  using Any = ::iggy::common::util::Any;

  ObjectFactory() = default;
  virtual ~ObjectFactory() {}

  virtual Any NewInstance() {
    return Any();
  }

  DISALLOW_MOVE(ObjectFactory);
  DISALLOW_COPY_AND_ASSIGN(ObjectFactory);
};

using ObjectFactoryMap = std::unordered_map<std::string, ObjectFactory*>;
using BaseClassFactoryMap = std::unordered_map<std::string, ObjectFactoryMap>;

BaseClassFactoryMap& GlobalBaseClassFactoryMap();

bool GetRegisteredDerivedClassNames(
    const std::string &base_class_name,
    std::vector<std::string> *registered_derived_class_names);

}  // namespace factory
}  // namespace common
}  // namespace iggy

#define REGISTER_BASE_CLASS_FACTORY(base_class)                               \
  class base_class##Factory {                                                 \
    using Any = ::iggy::common::util::Any;                                    \
    using ObjectFactoryMap = ::iggy::common::factory::ObjectFactoryMap;       \
   public:                                                                    \
    static base_class* GetInstancePtrByName(const std::string &name) {        \
      ObjectFactoryMap &obj_factory_map =                                     \
          ::iggy::common::factory::GlobalBaseClassFactoryMap()[#base_class];  \
      auto iter = obj_factory_map.find(name);                                 \
      if (iter == obj_factory_map.end()) {                                    \
        std::cerr << "Get instance " << name << " failed.\n";                 \
        return nullptr;                                                       \
      }                                                                       \
      Any obj = iter->second->NewInstance();                                  \
      return *(obj.AnyCast<base_class*>());                                   \
    }                                                                         \
  }

#define REGISTER_SUB_CLASS_BY_NAME(base_class, sub_class_name)                \
  namespace {                                                                 \
  using Any = ::iggy::common::util::Any;                                      \
  using ObjectFactory = ::iggy::common::factory::ObjectFactory;               \
  using ObjectFactoryMap = ::iggy::common::factory::ObjectFactoryMap;         \
  class sub_class_name##ObjectFactory : public ObjectFactory {                \
   public:                                                                    \
    virtual ~sub_class_name##ObjectFactory() {}                               \
    virtual Any NewInstance() {                                               \
      return Any(new sub_class_name());                                       \
    }                                                                         \
  };                                                                          \
  __attribute__((constructor))                                                \
  void Register##sub_class_name##ObjectFactory() {                            \
    ObjectFactoryMap &obj_factory_map =                                       \
        ::iggy::common::factory::GlobalBaseClassFactoryMap()[#base_class];    \
    if (obj_factory_map.find(#sub_class_name) == obj_factory_map.end()) {     \
      obj_factory_map[#sub_class_name] = new sub_class_name##ObjectFactory(); \
    }                                                                         \
  }                                                                           \
  }  // namespace

#endif  // IGGY_COMMON_FACTORY_AUTOREG_FACTORY_H_
