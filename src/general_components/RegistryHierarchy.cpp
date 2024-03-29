//
// Created by kgb on 22.07.2020.
//
#include "RegistryHierarchy.h"

unique_ptr<MainRegistry> MainRegistry::_mainRegistry;

entt::entity MainRegistry::CreateEntity()
{
    entt::entity newEntity = (_mainRegistry->enttRegistry->create());
    _mainRegistry->enttRegistry->emplace<TransformComponent>(newEntity);
    return newEntity;
}

//TODO: consider making this a const pointer to a const value
entt::registry * MainRegistry::GetMainRegistry()
{
    if(_mainRegistry)
        return _mainRegistry->enttRegistry.get();
    _mainRegistry = unique_ptr<MainRegistry>(new MainRegistry());
    return _mainRegistry->enttRegistry.get();
}

MainRegistry::MainRegistry()
{
    enttRegistry = make_unique<entt::registry>();
}

MainRegistry::~MainRegistry()
{
}
