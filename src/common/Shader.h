//
// Created by kgb on 14.07.2020.
//
#ifndef FRACTAL_RENDERER_SHADER_H
#define FRACTAL_RENDERER_SHADER_H

#include <iostream>
#include <GL/gl3w.h>

class Shader
{
public:
    ~Shader();
    Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
    GLuint shaderID;
};


#endif //FRACTAL_RENDERER_SHADER_H
