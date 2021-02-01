//
// Created by kgb on 14.07.2020.
//

#include "GLShader.h"
#include "LoadShader.h"
#include <glm/gtc/type_ptr.hpp>


GLShader::GLShader(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    shaderID = LoadShaders(vertexShaderPath, fragmentShaderPath );
}

GLShader::GLShader()
{
    shaderID = LoadShaders("../shaders/vertex.glsl", "../shaders/fragment.glsl");
}

GLShader::~GLShader()
{
    if(isDestructible)
    {
        glDeleteProgram(shaderID);
    }
}

GLShader &GLShader::operator=(GLShader &&f) noexcept
{
    f.isDestructible = false;
    this->shaderID = f.shaderID;
    this->isDestructible = true;
    return *this;
}

GLShader::GLShader(GLShader &&f) noexcept : shaderID(f.shaderID)
{
    f.isDestructible = false;
    isDestructible = true;
}

void GLShader::SetVec3(const glm::vec3& vec3, const char* uniformName)
{
    glUniform3fv(glGetUniformLocation(shaderID, uniformName), 1, glm::value_ptr(vec3));
}

void GLShader::SetMat4(const glm::mat4& mat4, const char* uniformName)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, uniformName), 1, GL_FALSE, glm::value_ptr(mat4));
}
void GLShader::SetTex(int texId, const char* uniformName)
{
    glUniform1i(glGetUniformLocation(shaderID, uniformName), texId);
}

void GLShader::SetFloat(float floatVal, const char* uniformName)
{
    glUniform1f(glGetUniformLocation(shaderID, uniformName), floatVal);
}

void GLShader::SetInt(int intVal, const char* uniformName)
{
    glUniform1i(glGetUniformLocation(shaderID, uniformName), intVal);
}

void GLShader::SetMaterialStruct(const struct BasicMaterial &material) {
    glUniform3fv(glGetUniformLocation(shaderID, "material.ambient"), 1, glm::value_ptr(material.ambient));
    glUniform3fv(glGetUniformLocation(shaderID, "material.diffuse"), 1, glm::value_ptr(material.diffuse));
    glUniform3fv(glGetUniformLocation(shaderID, "material.specular"), 1, glm::value_ptr(material.specular));
    glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), material.shininess);
}

void GLShader::SetDirectionalLight(const DirectionalLightComponent &light)
{
    SetVec3(light.direction, "directionLight.direction");
    SetVec3(light.color, "directionLight.color");

}

void GLShader::SetPointLight(const PointLightComponent &light, const TransformComponent& transform, int idx)
{

    std::string first("pointLights[");
    first += std::to_string(idx);
    first += std::string("].");
    SetFloat(light.quadraticTerm, (first + std::string("quadratic")).c_str());
    SetFloat(light.linearTerm, (first + std::string("linear")).c_str());
    SetFloat(light.constantTerm, (first + std::string("constant")).c_str());
    SetVec3(light.color, (first + std::string("color")).c_str());
    SetVec3(transform._position, (first + std::string("position")).c_str());
}

void GLShader::SetSpotLight(const SpotLightComponent& light, const TransformComponent& transform, int idx)
{
    std::string first("spotLights[");
    first += std::to_string(idx);
    first += std::string("].");
    SetFloat(light.spotlightAngle, (first + std::string("lightAngle")).c_str());
    SetVec3(light.color, (first + std::string("color")).c_str());
    SetVec3(transform._position, (first + std::string("position")).c_str());
    SetVec3(light.direction, (first + std::string("direction")).c_str());
}
