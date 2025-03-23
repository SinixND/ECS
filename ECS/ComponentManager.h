#ifndef IG20250323182928
#define IG20250323182928

#include "Component.h"
#include "DenseMap.h"
#include "EntityId.h"
#include <memory>
#include <unordered_map>

namespace snx
{
    class ComponentManager
    {
        std::unordered_map<ComponentTypeId, std::unique_ptr<IDenseMap<ComponentTypeId>>> componentContainersByTypeId_{};

    public:
        //* Create container for ComponentType
        template <typename ComponentType>
        void registerComponentType()
        {
            componentContainersByTypeId_[ComponentType::getId()] =
                std::make_unique<DenseMap<EntityId, ComponentType>>();
        }

        //* Assigns component to entity
        template <typename ComponentType>
        void assignTo(ComponentType const& component, Id entityId)
        {
            //* Check if container exists
            // if (!componentContainersByTypeId_.contains(ComponentType::getId()))
            // {
            //     registerComponentType<ComponentType>();
            // }

            //* Add component
            getComponentContainer<ComponentType>()->insert(entityId, component);
        }

        //* Access a specific component from a entity
        template <typename ComponentType>
        ComponentType& getFrom(EntityId entityId)
        {
            //* Check if entity exists
            // if (!testEntity<ComponentType>(entityId))
            // {
            //     return nullptr;
            // }

            // Return component
            return getComponentContainer<ComponentType>()->at(entityId);
        }

        //* Remove a component from an entity
        template <typename ComponentType>
        void removeFrom(EntityId entityId)
        {
            //* Check if container exists
            // if (testContainer<ComponentType>())
            // {
            //     return;
            // }

            //* Remove component
            getComponentContainer<ComponentType>()->erase(entityId);
        }

        void removeAllComponentsFrom(EntityId entityId)
        {
            for (auto const& [componentTypeId, container] : componentContainersByTypeId_)
            {
                container->erase(entityId);
            }
        }

        std::unordered_map<ComponentTypeId, std::unique_ptr<IDenseMap<EntityId>>>* getAllContainers()
        {
            return &componentContainersByTypeId_;
        }

    private:
        //* Check if container exists
        // template <typename ComponentType>
        // bool testContainer()
        // {
        //     return componentContainersByTypeId_.contains(ComponentType::getId());
        // }

        //* Check if entity exists in container
        // template <typename ComponentType>
        // bool testEntity(EntityId entityId)
        // {
        //     if (!testContainer<ComponentType>())
        //     {
        //         return false;
        //     }
        //
        //     return getComponentContainer<ComponentType>()->contains(entityId);
        // }

        //* Return pointer to concrete container
        template <typename ComponentType>
        DenseMap<EntityId, ComponentType>* getComponentContainer()
        {
            return dynamic_cast<DenseMap<EntityId, ComponentType>*>(
                componentContainersByTypeId_[ComponentType::getId()].get());
        }
    };

}

#endif
