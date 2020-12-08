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