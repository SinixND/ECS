#ifndef IG20250323182928
#define IG20250323182928

#include "DenseMap.h"
#include "EntityId.h"
#include "Id.h"
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace snx
{
    using ComponentTypeId = std::type_index;

    class ComponentManager
    {
        std::unordered_map<ComponentTypeId, std::shared_ptr<IDenseMap<EntityId>>> componentContainersByTypeId_{};

    public:
        //* Create container for ComponentType
        template <typename ComponentType>
        void registerType()
        {
            componentContainersByTypeId_[ComponentType::typeId()] =
                std::make_shared<DenseMap<Id, ComponentType>>();
        }

        //* Assigns component to entity
        template <typename ComponentType>
        void add(ComponentType const& component, Id entityId)
        {
            //* Check if container exists
            // if (!componentContainersByTypeId_.contains(ComponentType::typeId()))
            // {
            //     registerComponentType<ComponentType>();
            // }

            //* Add component
            getComponentContainer<ComponentType>()->insert(entityId, component);
        }

        //* Access a specific component from a entity
        template <typename ComponentType>
        ComponentType& get(Id entityId)
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
        void remove(Id entityId)
        {
            //* Check if container exists
            // if (testContainer<ComponentType>())
            // {
            //     return;
            // }

            //* Remove component
            getComponentContainer<ComponentType>()->erase(entityId);
        }

        void removeAll(Id entityId)
        {
            for (auto const& [componentTypeId, container] : componentContainersByTypeId_)
            {
                container->erase(entityId);
            }
        }

        std::unordered_map<ComponentTypeId, std::shared_ptr<IDenseMap<EntityId>>>* getAllContainers()
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
        // bool testEntity(Id entityId)
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
        DenseMap<Id, ComponentType>* getComponentContainer()
        {
            return std::static_pointer_cast<DenseMap<Id, ComponentType>>(
                componentContainersByTypeId_[ComponentType::getId()]);
        }
    };
}

#endif
