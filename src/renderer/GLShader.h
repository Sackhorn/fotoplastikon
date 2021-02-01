//
// Created by kgb on 14.07.2020.
//
#ifndef FRACTAL_RENDERER_GLSHADER_H
#define FRACTAL_RENDERER_GLSHADER_H

#include <GL/gl3w.h>
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "SpotLightComponent.h"
#include "TransformComponent.h"

using namespace glm;

struct BasicMaterial
{
    vec3 ambient=vec3(0.1);
    vec3 diffuse=vec3(1.0);
    vec3 specular=vec3(0.5f);
    float shininess=16.5f;
};

class GLShader
{
private:
    bool isDestructible = true;
public:
    GLuint shaderID;
    ~GLShader();
    GLShader();
    GLShader(GLShader&& f) noexcept ;
    GLShader& operator=(GLShader&& f) noexcept;
    GLShader(const char *vertexShaderPath, const char *fragmentShaderPath);
    void SetVec3(const glm::vec3& vec3, const char *uniformName);
    void SetMat4(const glm::mat4& mat4, const char *uniformName);
    void SetFloat(float floatVal, const char *uniformName);
    void SetInt(int intVal, const char *uniformName);
    void SetTex(int texId, const char *uniformName);
    void SetMaterialStruct(const struct BasicMaterial& material);
    void SetDirectionalLight(const DirectionalLightComponent& light);
    void SetPointLight(const PointLightComponent& light, const TransformComponent& transform, int idx);
    void SetSpotLight(const SpotLightComponent &light, const TransformComponent &transform, int idx);
};

#endif //FRACTAL_RENDERER_GLSHADER_H
