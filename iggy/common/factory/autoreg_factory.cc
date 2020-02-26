// Copyright 2020 insaneyilin All Rights Reserved.

#include "iggy/common/factory/autoreg_factory.h"

namespace iggy {
namespace common {
namespace factory {

BaseClassFactoryMap& GlobalBaseClassFactoryMap() {
  static BaseClassFactoryMap base_factory_map;
  return base_factory_map;
}

bool GetRegisteredDerivedClassNames(
    const std::string &base_class_name,
    std::vector<std::string> *registered_derived_class_names) {
  if (!registered_derived_class_names) {
    return false;
  }
  BaseClassFactoryMap &base_factory_map = GlobalBaseClassFactoryMap();
  auto iter = base_factory_map.find(base_class_name);
  if (iter == base_factory_map.end()) {
    std::cerr << "base class not registered: " << base_class_name << "\n";
    return false;
  }
  registered_derived_class_names->clear();
  for (auto pr : iter->second) {
    registered_derived_class_names->push_back(pr.first);
  }
  return true;
}

}  // namespace factory
}  // namespace common
}  // namespace iggy
