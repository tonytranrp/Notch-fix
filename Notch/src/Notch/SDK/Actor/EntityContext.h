#pragma once
#include "../../Libraries/Libs/entt/entt/entt.hpp"
#include "EntityId.h"
class EntityRegistry {};

class EntityContext {
public:
    EntityRegistry* mRegistry;
    entt::basic_registry<EntityId>& mEnttRegistry;
    EntityId mEntity;

    [[nodiscard]] inline entt::basic_registry<EntityId>& getRegistry()
    {
        return mEnttRegistry;
    }

    [[nodiscard]] inline entt::basic_registry<EntityId> const& getRegistry() const
    {
        return mEnttRegistry;
    }
};