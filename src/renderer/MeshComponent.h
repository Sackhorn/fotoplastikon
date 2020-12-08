//
// Created by kgb on 18.07.2020.
//

#ifndef FRACTAL_RENDERER_MESHCOMPONENT_H
#define FRACTAL_RENDERER_MESHCOMPONENT_H

#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <string>
#include <utility>
#include <vector>
#include <MaterialComponent.h>
using namespace std;
using namespace glm;

struct Vertex {
    vec3 Position;
    vec3 Normal;
    vec3 TexCoords;

};

class MeshComponent
{
    string _meshPath;
    bool _destroyable = true;
    void LoadMesh();
public:
    unique_ptr<unsigned int> VBO, VAO, EBO;
    unique_ptr<MaterialComponent> materialComponent;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    explicit MeshComponent(string meshPath);
    ~MeshComponent();
    MeshComponent(MeshComponent&& f) noexcept ;
    void PushToBuffer();
    MeshComponent& operator=(MeshComponent&& f) noexcept;

    int loadingFlags = aiProcess_CalcTangentSpace|
                                             aiProcess_GenSmoothNormals|
                                             aiProcess_Triangulate|
                                             aiProcess_JoinIdenticalVertices;

};


#endif //FRACTAL_RENDERER_MESHCOMPONENT_H
