#ifndef SYSTEMMANAGER_H_20240103210800
#define SYSTEMMANAGER_H_20240103210800

#include "Id.h"
#include "Signature.h"
#include "System.h"
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace snx
{
    using SystemTypeId = std::type_index;

    class SystemManager
    {
        std::unordered_map<SystemTypeId, std::shared_ptr<System>> systemTypeToSystem_;
        std::unordered_map<SystemTypeId, Signature> systemTypeToSignature_;

    public:
        template <typename SystemType>
        [[nodiscard]] std::shared_ptr<SystemType> registerSystem()
        {
            auto system = std::make_shared<SystemType>();

            systemTypeToSystem_.insert({typeid(SystemType), system});
            systemTypeToSignature_.insert({typeid(SystemType), Signature{}});

            return system;
        }

        template <typename SystemType, typename ComponentType>
        void setSignature()
        {
            systemTypeToSignature_.at(typeid(SystemType)).set(ComponentType::typeId());
        }

        void registerEntity(Id entityId, Signature entitySignature)
        {
            for (auto [systemId, systemSignature] : systemTypeToSignature_)
            {
                if (systemSignature == entitySignature)
                {
                    systemTypeToSystem_.at(systemId)->entities.insert(entityId);
                }
            }
        }

        void unregisterEntity(Id entityId)
        {
            for (auto [systemId, systemSignature] : systemTypeToSignature_)
            {
                systemTypeToSystem_.at(systemId)->entities.erase(entityId);
            }
        }

        void unregisterEntity(Id entityId, Signature entitySignature)
        {
            for (auto [systemId, systemSignature] : systemTypeToSignature_)
            {
                if (systemSignature != entitySignature)
                {
                    systemTypeToSystem_.at(systemId)->entities.erase(entityId);
                }
            }
        }
    };
}

#endif
