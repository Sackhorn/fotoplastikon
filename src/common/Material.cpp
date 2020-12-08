//
// Created by kgb on 14.07.2020.
//

#include "Material.h"
#include "../../libs/Simple-OpenGL-Image-Library/src/SOIL.h"
#include <assert.h>

Material::Material(const char *albedoPath) {
    int width, height, channels;
    unsigned char* albedo = SOIL_load_image(albedoPath, &width, &height, &channels, SOIL_LOAD_RGBA);
    assert(("failed to load albedo texture", albedo));
    glGenTextures(1, &Albedo);
    glBindTexture(GL_TEXTURE_2D, Albedo);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, albedo);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(albedo);
    glUseProgram(shaderID);
    glUniform1i(glGetUniformLocation(shaderID, "albedo"), 0);

}
