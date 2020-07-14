//
// Created by kgb on 12.07.2020.
//

#include "StaticMesh.h"


StaticMesh::StaticMesh(string FileName) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(FileName, aiProcess_CalcTangentSpace);
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

    SetupMesh();
}

void StaticMesh::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

StaticMesh::~StaticMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void StaticMesh::Draw(const Material& material)
{
    glUseProgram(material.shaderID);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
