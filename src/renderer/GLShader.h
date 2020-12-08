//
// Created by kgb on 14.07.2020.
//
#ifndef FRACTAL_RENDERER_GLSHADER_H
#define FRACTAL_RENDERER_GLSHADER_H

#include <GL/gl3w.h>
#include <iostream>
#include <glm/glm.hpp>

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

    void SetTex(int texId, const char *uniformName);
};

#endif //FRACTAL_RENDERER_GLSHADER_H
