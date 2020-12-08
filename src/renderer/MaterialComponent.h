//
// Created by kgb on 18.07.2020.
//

#ifndef FRACTAL_RENDERER_MATERIALCOMPONENT_H
#define FRACTAL_RENDERER_MATERIALCOMPONENT_H

#include "GLShader.h"
#include "Texture.h"
#include <GL/gl3w.h>

class MaterialComponent
{
public:
    std::unique_ptr<Texture> albedo;
    std::unique_ptr<GLShader> shader;
    MaterialComponent();
    explicit MaterialComponent(const char* texturePath);
    ~MaterialComponent();
    MaterialComponent(MaterialComponent&& f) noexcept;
    MaterialComponent& operator=(MaterialComponent&& f) noexcept;
};


#endif //FRACTAL_RENDERER_MATERIALCOMPONENT_H
