#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normal_modelspace;
layout(location = 2) in vec3 TexCoords_model;

out vec3 FragPos;
out vec3 Normal;
out vec3 TexCoords;

uniform mat4 wvp;
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    FragPos = vec3(world * vec4(vertexPosition_modelspace, 1.0));
    Normal = mat3(transpose(inverse(world))) * normal_modelspace;
    TexCoords = TexCoords_model;
    gl_Position = wvp *  vec4(vertexPosition_modelspace, 1.0);
}
