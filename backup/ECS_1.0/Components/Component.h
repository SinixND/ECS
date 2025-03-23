#ifndef COMPONENT_H_20231219002351
#define COMPONENT_H_20231219002351

#include "ComponentTypeId.h"

namespace snx {
struct IComponent {
  virtual ~IComponent() = default;

protected:
  static inline ComponentTypeId componentTypeId_{0};
};

template <typename ComponentType> class Component : public IComponent {
public:
  static inline ComponentTypeId getId() {
    static ComponentTypeId id{
        ++componentTypeId_}; // Initialized only once per templated type because
                             // it is static
    return id;
  }
};
} // namespace snx

#endif
