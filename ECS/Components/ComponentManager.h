#ifndef COMPONENTMANAGER_H_20240101214521
#define COMPONENTMANAGER_H_20240101214521

#include "Component.h"
#include "ComponentTypeId.h"
#include "EntityId.h"
#include "SparseSet.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace snx
{
    class ComponentManager
    {
    public:
        //* Register component to avoid Segmentation fault

        // Add component to entity
        template <typename ComponentType>
        void assignTo(EntityId entityId, const ComponentType& component)
        {
            // Check if container exists
            if (!componentContainersByTypeId_.contains(getId<ComponentType>()))
            {
                registerComponentType<ComponentType>();
            }

            // Add component
            getComponentContainer<ComponentType>()->insert(entityId, component);
        }

        // Remove a component from an entity
        template <typename ComponentType>
        void removeFrom(EntityId entityId)
        {
            // Check if entity exists
            if (!testEntity<ComponentType>(entityId))
            {
                return;
            }

            // Remove component
            getComponentContainer<ComponentType>()->erase(entityId);
        }

        // Access a component from a specific entity
        template <typename ComponentType>
        ComponentType* getFrom(EntityId entityId)
        {
            // Check if entity exists
            if (!testEntity<ComponentType>(entityId))
            {
                return nullptr;
            }

            // Return component
            return getComponentContainer<ComponentType>()->get(entityId);
        }

        // Access all components
        template <typename ComponentType>
        std::vector<ComponentType>* getAllComponents()
        {
            // Check if container exists
            if (!testContainer<ComponentType>())
            {
                return nullptr;
            }

            // Return vector of components
            return getComponentContainer<ComponentType>()->getAllElements();
        }

        std::unordered_map<ComponentTypeId, std::shared_ptr<ISparseSet<EntityId>>>*
        getAllContainers()
        {
            return &componentContainersByTypeId_;
        }

        // Get unique entity
        template <typename ComponentType>
        EntityId getFirstEntity()
        {
            // Check if container exists
            if (!testContainer<ComponentType>())
            {
                return 0;
            }

            // Return entity
            return getComponentContainer<ComponentType>()->getFirstKey();
        }
        // Get all entities
        template <typename ComponentType>
        std::unordered_set<EntityId>* getAllEntities()
        {
            // Check if container exists
            if (!testContainer<ComponentType>())
            {
                return nullptr;
            }

            // Return set of entities
            return getComponentContainer<ComponentType>()->getAllKeys();
        }

    private:
        std::unordered_map<ComponentTypeId, std::shared_ptr<ISparseSet<EntityId>>>
            componentContainersByTypeId_{};

    private:
        // Check if entity exists in container
        template <typename ComponentType>
        bool testEntity(EntityId entityId)
        {
            if (!testContainer<ComponentType>())
            {
                return false;
            }

            return getComponentContainer<ComponentType>()->test(entityId);
        }

        // Check if entity exists in container
        bool testEntity(std::shared_ptr<ISparseSet<EntityId>> container, EntityId entityId)
        {
            return container->test(entityId);
        }

        // Check if container exists
        template <typename ComponentType>
        bool testContainer()
        {
            [[maybe_unused]] auto dbg{getId<ComponentType>()};
            return componentContainersByTypeId_.contains(getId<ComponentType>());
        }

        // Get component type id
        template <typename ComponentType>
        ComponentTypeId getId()
        {
            return Component<ComponentType>::getId();
        }

        // Register component type
        template <typename ComponentType>
        void registerComponentType()
        {
            componentContainersByTypeId_[getId<ComponentType>()] =
                std::make_shared<SparseSet<EntityId, ComponentType>>();
        }

        // Return specialized container pointer
        template <typename ComponentType>
        std::shared_ptr<SparseSet<EntityId, ComponentType>> getComponentContainer()
        {
            return std::static_pointer_cast<SparseSet<EntityId, ComponentType>>(
                componentContainersByTypeId_[getId<ComponentType>()]);
        }
    };
} // namespace snx

#endif
