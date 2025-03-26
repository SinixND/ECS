#ifndef IG20250323182047
#define IG20250323182047

#include "ComponentManager.h"
#include "Id.h"
#include "IdManager.h"

namespace snx
{
    class ECS
    {
        IdManager idManager_;
        ComponentManager componentManager_;

    public:
        //* Entities
        //* ============================
        Id createEntity()
        {
            return idManager_.requestId();
        }

        void removeEntity(Id entityId)
        {
            componentManager_.removeAll(entityId);
            idManager_.suspendId(entityId);
        }

        //* Components
        //* ============================
        template <typename ComponentType>
        void registerComponentType()
        {
            componentManager_.registerType<ComponentType>();
        }

        template <typename ComponentType>
        void assignComponent(ComponentType const& component, Id entityId)
        {
            //* Assign component to entity
            componentManager_.add(component, entityId);
        }

        template <typename ComponentType>
        ComponentType& getComponent(Id entityId)
        {
            // Return component
            return componentManager_.get<ComponentType>(entityId);
        }

        template <typename ComponentType>
        void removeComponent(Id entityId)
        {
            // Remove component from entity
            componentManager_.remove<ComponentType>(entityId);
        }
    };
}

#endif
