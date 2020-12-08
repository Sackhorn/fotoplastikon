//
// Created by kgb on 18.07.2020.
//


#include "MaterialComponent.h"

MaterialComponent::MaterialComponent()
{
    shader = std::make_unique<GLShader>();
    albedo = std::make_unique<Texture>();
}

MaterialComponent::MaterialComponent(const char *texture) {
    shader = std::make_unique<GLShader>();
    albedo = std::make_unique<Texture>(texture);
}

MaterialComponent::~MaterialComponent()
{
}

MaterialComponent::MaterialComponent(MaterialComponent &&f) noexcept : shader(std::move(f.shader)), albedo(std::move(f.albedo))
{
}

MaterialComponent &MaterialComponent::operator=(MaterialComponent &&f) noexcept
{
    shader = std::move(f.shader);
    albedo = std::move(f.albedo);
    return *this;
}
