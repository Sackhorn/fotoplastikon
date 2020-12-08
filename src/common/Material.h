//
// Created by kgb on 14.07.2020.
//

#ifndef FRACTAL_RENDERER_MATERIAL_H
#define FRACTAL_RENDERER_MATERIAL_H
#include <GLShader.h>
#include <GL/gl3w.h>


class Material {
    Shader materialShader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl" );
    GLuint Albedo;
public:
    explicit Material(const char* albedoPath);
    GLuint shaderID = materialShader.shaderID;
};


#endif //FRACTAL_RENDERER_MATERIAL_H
