#ifndef IG20250325230919
#define IG20250325230919

#include "EntityId.h"
#include "Id.h"
#include "IdManager.h"
#include "Signature.h"
#include <unordered_map>

namespace snx
{
    class EntityManager
    {
        IdManager idManager_;
        std::unordered_map<EntityId, Signature> entityToSignature_;

    public:
        Id createEntity()
        {
            return idManager_.requestId();
        }

        void deleteEntity(EntityId entityId)
        {
            entityToSignature_[entityId].reset();

            idManager_.suspendId(entityId);
        }

        void setSignature(EntityId entityId, Signature const& signature)
        {
            entityToSignature_[entityId] = signature;
        }

        Signature const& getSignature(EntityId entityId)
        {
            return entityToSignature_[entityId];
        }
    };
}

#endif
