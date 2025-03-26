#ifndef SYSTEMMANAGER_H_20240103210800
#define SYSTEMMANAGER_H_20240103210800

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
        std::shared_ptr<SystemType> registerType()
        {
            auto system = std::make_shared<SystemType>();

            systemTypeToSystem_.insert({typeid(SystemType), system});

            return system;
        }

        template <typename SystemType>
        void setSignature(Signature const& signature)
        {
            systemTypeToSignature_.insert({typeid(SystemType), signature});
        }
    };
}

#endif
