#ifndef IG20250325230919
#define IG20250325230919

#include "Entity.h"
#include "Id.h"
#include "IdManager.h"
#include "Signature.h"
#include <unordered_map>

namespace snx
{
    class EntityManager
    {
        IdManager idManager_;
        std::unordered_map<Entity, Signature> entityToSignature_;

    public:
        Id createEntity()
        {
            Id entity = idManager_.requestId();

            entityToSignature_.insert({entity, Signature{}});

            return entity;
        }

        void deleteEntity(Entity entityId)
        {
            entityToSignature_.at(entityId).reset();

            idManager_.suspendId(entityId);
        }

        void setSignature(Entity entityId, Id componentTypeId)
        {
            entityToSignature_.at(entityId).set(componentTypeId);
        }

        void resetSignature(Entity entityId, Id componentTypeId)
        {
            entityToSignature_.at(entityId).reset(componentTypeId);
        }

        Signature const& getSignature(Entity entityId)
        {
            return entityToSignature_[entityId];
        }
    };
}

#endif
