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

        void removeEntity(EntityId entityId)
        {
            componentManager_.removeAllComponentsFrom(entityId);
            idManager_.suspendId(entityId);
        }

        //* Components
        //* ============================
        template <typename ComponentType>
        void registerComponentType()
        {
            componentManager_.registerComponentType<ComponentType>();
        }

        template <typename ComponentType>
        void assignComponent(ComponentType const& component, Id entityId)
        {
            //* Assign component to entity
            componentManager_.assignTo(component, entityId);
        }

        template <typename ComponentType>
        ComponentType& getComponent(EntityId entityId)
        {
            // Return component
            return componentManager_.getFrom<ComponentType>(entityId);
        }

        template <typename ComponentType>
        void removeComponent(EntityId entityId)
        {
            // Remove component from entity
            componentManager_.removeFrom<ComponentType>(entityId);
        }
    };
}

#endif
