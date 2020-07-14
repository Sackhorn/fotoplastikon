//
// Created by kgb on 12.07.2020.
//
#ifndef FRACTAL_RENDERER_STATICMESH_H
#define FRACTAL_RENDERER_STATICMESH_H

#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <Shader.h>
#include "Material.h"

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 TexCoords;

};

class StaticMesh {
public:
    explicit StaticMesh(string FileName);
    ~StaticMesh();
    void Draw(const Material& material);
    void Draw();
private:
    Material* implicitMaterial = nullptr;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    unsigned int VBO, VAO, EBO;
    void SetupMesh();
};


#endif //FRACTAL_RENDERER_STATICMESH_H
