#ifndef SYSTEMMANAGER_H_20240103210800
#define SYSTEMMANAGER_H_20240103210800

#include "System.h"
#include <memory>
#include <vector>

namespace snx
{
    class SystemManager
    {
    public:
        template <typename SystemType>
        SystemType* registerSystem(ECS* ecs)
        {
            auto system{std::make_unique<SystemType>(ecs)};

            systems_.push_back(system);
            return &system;
        }

        std::vector<std::shared_ptr<ISystem>>* getSystems() { return &systems_; }

    private:
        std::vector<std::shared_ptr<ISystem>> systems_;
    };
} // namespace snx

#endif
