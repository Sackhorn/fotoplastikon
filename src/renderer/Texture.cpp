//
// Created by kgb on 23.07.2020.
//

#include "Texture.h"
#include "../../libs/Simple-OpenGL-Image-Library/src/SOIL.h"
#include <assert.h>

Texture::Texture()
{
    filePath = "../mesh/test.jpg";
    LoadTexture();
}

Texture::Texture(const char *filePath) : filePath(filePath)
{
    LoadTexture();
}

Texture::~Texture() {
    if(isDeletable)
    {
        glDeleteTextures(1, &textureID);
    }
}

Texture::Texture(Texture &&f) noexcept : textureID(f.textureID), filePath(f.filePath)
{
    f.isDeletable = false;
}

Texture &Texture::operator=(Texture &&f) noexcept
{
    textureID = f.textureID;
    filePath = f.filePath;
    f.isDeletable = false;
    return *this;
}

void Texture::LoadTexture() {
    int width, height, channels;
    unsigned char* albedo = SOIL_load_image(filePath, &width, &height, &channels, SOIL_LOAD_RGBA);
    assert(("failed to load albedo texture", albedo));
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0 + textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, albedo);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(albedo);
}