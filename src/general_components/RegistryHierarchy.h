//
// Created by kgb on 18.07.2020.
//

#ifndef FRACTAL_RENDERER_REGISTRYHIERARCHY_H
#define FRACTAL_RENDERER_REGISTRYHIERARCHY_H


#include <entt/entt.hpp>
#include "TransformComponent.h"
class MainRegistry
{
private:
    MainRegistry();
public:
    static MainRegistry* _mainRegistry;
    unique_ptr<entt::registry> enttRegistry;
    static entt::registry * GetMainRegistry();
    static entt::entity createEntity();
    ~MainRegistry();
};


#endif //FRACTAL_RENDERER_REGISTRYHIERARCHY_H