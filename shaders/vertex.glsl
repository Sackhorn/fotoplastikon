#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normal_modelspace;
layout(location = 2) in vec3 TexCoords_model;
out vec3 Normal;
out vec3 TexCoords;

void main(){

//    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
    Normal = normal_modelspace;
    TexCoords = TexCoords_model;
}
