#ifndef IG20250323182928
#define IG20250323182928

#include "DenseMap.h"
#include "Entity.h"
#include "Id.h"
#include <memory>
#include <unordered_map>

namespace snx
{
    using ComponentTypeId = Id;

    class ComponentManager
    {
        std::unordered_map<ComponentTypeId, std::shared_ptr<IDenseMap<Entity>>> componentContainersByTypeId_{};

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
            //* Add component
            getComponentContainer<ComponentType>()->insert(entityId, component);
        }

        //* Access a specific component from a entity
        template <typename ComponentType>
        ComponentType& get(Id entityId)
        {
            // Return component
            return getComponentContainer<ComponentType>()->at(entityId);
        }

        //* Remove a component from an entity
        template <typename ComponentType>
        void remove(Id entityId)
        {
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

        std::unordered_map<ComponentTypeId, std::shared_ptr<IDenseMap<Entity>>>* getAllContainers()
        {
            return &componentContainersByTypeId_;
        }

    private:
        //* Return pointer to concrete container
        template <typename ComponentType>
        std::shared_ptr<DenseMap<Id, ComponentType>> getComponentContainer()
        {
            return std::static_pointer_cast<DenseMap<Id, ComponentType>>(
                componentContainersByTypeId_.at(ComponentType::typeId()));
        }
    };
}

#endif
