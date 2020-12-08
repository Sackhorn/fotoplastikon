//
// Created by kgb on 23.07.2020.
//

#ifndef FRACTAL_RENDERER_TEXTURE_H
#define FRACTAL_RENDERER_TEXTURE_H

#include <GL/gl3w.h>



class Texture {
    const char* filePath;
    bool isDeletable = true;
    void LoadTexture();
public:
    unsigned int textureID;
    ~Texture();
    Texture();
    explicit Texture(const char* filePath);
    Texture(Texture&& f) noexcept ;
    Texture& operator=(Texture&& f) noexcept ;
};


#endif //FRACTAL_RENDERER_TEXTURE_H
