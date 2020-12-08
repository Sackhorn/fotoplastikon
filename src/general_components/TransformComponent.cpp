//
// Created by kgb on 18.07.2020.
//
#include "TransformComponent.h"

TransformComponent::TransformComponent(vec3 position, vec3 scaleArg, vec3 rotation):
        _position(position),
        _scale(scaleArg),
        _rotation(rotation),
        world(mat4(1.0))
{
    UpdateMatrices();
}

TransformComponent::TransformComponent() :
        _position(vec3(0.0)),
        _scale(vec3(1.0)),
        _rotation(vec3(0.0)),
        world(mat4(1.0))
{
    UpdateMatrices();
}

void TransformComponent::UpdateMatrices()
{
    world = getWorldMatrix(*this);
}

mat4 TransformComponent::getWorldMatrix(const TransformComponent& transform)
{
    mat4 world = mat4(1.0);
    world = translate(world, transform._position);
    world = rotate(world, transform._rotation.x, vec3(1,0,0));
    world = rotate(world, transform._rotation.y, vec3(0, 1,0));
    world = rotate(world, transform._rotation.z, vec3(0,0,1));
    world = scale(world, transform._scale);
    return world;
}

