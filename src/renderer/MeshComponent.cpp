//
// Created by kgb on 18.07.2020.
//

#include "MeshComponent.h"
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>

//static const unsigned int loadingFlags = aiProcess_CalcTangentSpace|
//                                        aiProcess_GenSmoothNormals|
//                                        aiProcess_Triangulate|
//                                        aiProcess_JoinIdenticalVertices;
//
MeshComponent::MeshComponent(string meshPath) : _meshPath(std::move(meshPath))
{
    materialComponent = make_unique<MaterialComponent>();
    VAO = make_unique<unsigned int>();
    EBO = make_unique<unsigned int>();
    VBO = make_unique<unsigned int>();
    LoadMesh();
}

MeshComponent::~MeshComponent()
{
    if(_destroyable)
    {
        glDeleteVertexArrays(1, VAO.get());
        glDeleteBuffers(1, VBO.get());
        glDeleteBuffers(1, EBO.get());
//        delete VAO;
//        delete VBO;
//        delete EBO;
    }
}

void MeshComponent::LoadMesh() {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(_meshPath, loadingFlags);
    auto mesh = scene->mMeshes;
    auto singleMesh = mesh[0];
    for(unsigned int i=0; i < singleMesh->mNumVertices; i++)
    {
        Vertex vertex{};

        vertex.Position.x = singleMesh->mVertices[i].x;
        vertex.Position.y = singleMesh->mVertices[i].y;
        vertex.Position.z = singleMesh->mVertices[i].z;

        vertex.Normal.x = singleMesh->mNormals[i].x;
        vertex.Normal.y = singleMesh->mNormals[i].y;
        vertex.Normal.z = singleMesh->mNormals[i].z;

        vertex.TexCoords.x = singleMesh->mTextureCoords[0][i].x;
        vertex.TexCoords.y = singleMesh->mTextureCoords[0][i].y;
        vertex.TexCoords.z = singleMesh->mTextureCoords[0][i].z;

        vertices.push_back(vertex);
    }

    for(unsigned int i=0; i < singleMesh->mNumFaces; i++)
    {
        for(unsigned int j=0; j < singleMesh->mFaces[i].mNumIndices; j++)
        {
            indices.push_back(singleMesh->mFaces[i].mIndices[j]);
        }
    }

    PushToBuffer();
}

void MeshComponent::PushToBuffer() {
    glGenVertexArrays(1, VAO.get());
    glGenBuffers(1, VBO.get());
    glGenBuffers(1, EBO.get());

    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

}

MeshComponent::MeshComponent(MeshComponent && f) noexcept : VAO(std::move(f.VAO)),
                                                   VBO(std::move(f.VBO)),
                                                   EBO(std::move(f.EBO)),
                                                   materialComponent(std::move(f.materialComponent)),
                                                   _meshPath(f._meshPath)
{
    f._destroyable = false;
    indices = f.indices;
    vertices = f.vertices;
//    LoadMesh();
}

MeshComponent &MeshComponent::operator=(MeshComponent &&f)  noexcept
{
    VBO = std::move(f.VAO);
    EBO = std::move(f.EBO);
    VAO = std::move(f.VAO);
    materialComponent = std::move(f.materialComponent);
    _meshPath = f._meshPath;
    f._destroyable = false;
    indices = std::move(f.indices);
    vertices = f.vertices;
//    LoadMesh();
    return *this;
}
