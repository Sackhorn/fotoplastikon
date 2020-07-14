//
// Created by kgb on 14.07.2020.
//

#include "Shader.h"
#include <LoadShader.hpp>


Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
    shaderID = LoadShaders(vertexShaderPath, fragmentShaderPath );
}

Shader::~Shader() {
    glDeleteProgram(shaderID);
}


