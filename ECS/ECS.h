#ifndef IG20250323182047
#define IG20250323182047

#include "ComponentManager.h"
#include "EntityManager.h"
#include "Id.h"
#include "SystemManager.h"
#include <memory>

namespace snx
{
    class ECS
    {
        EntityManager entityManager_;
        ComponentManager componentManager_;
        SystemManager systemManager_;

    public:
        //* Entities
        //* ============================
        Id createEntity()
        {
            return entityManager_.createEntity();
        }

        void removeEntity(Id entityId)
        {
            componentManager_.removeAll(entityId);

            systemManager_.unregisterEntity(entityId);

            entityManager_.deleteEntity(entityId);
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

            //* Update entity signature
            entityManager_.setSignature(entityId, ComponentType::typeId());

            //* Notify systems that entity signature changed
            systemManager_.registerEntity(
                entityId,
                entityManager_.getSignature(entityId));
        }

        template <typename ComponentType>
        ComponentType& getComponent(Id entityId)
        {
            return componentManager_.get<ComponentType>(entityId);
        }

        template <typename ComponentType>
        void removeComponent(Id entityId)
        {
            //* Remove component from entity
            componentManager_.remove<ComponentType>(entityId);

            //* Update entity signature
            entityManager_.resetSignature(entityId, ComponentType::typeId());

            //* Notify systems that entity signature changed
            systemManager_.unregisterEntity(
                entityId,
                entityManager_.getSignature(entityId));
        }

        //* Systems
        //* ============================
        template <typename SystemType>
        [[nodiscard]] std::shared_ptr<SystemType> registerSystem()
        {
            return systemManager_.registerSystem<SystemType>();
        }

        template <typename SystemType, typename ComponentType>
        void setSystemSignature()
        {
            systemManager_.setSignature<SystemType, ComponentType>();
        }
    };
}

#endif
