#pragma once

#include <glad/glad.h>

class Texture {
public:
    // texture ID
    unsigned int ID;
    // texture dimensions (from image loaded to texture)
    unsigned int Width, Height;
    unsigned int internal_f;
    unsigned int image_f;
    // default constructor
    Texture();
    // generate texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    // bind texture to current active GL_TEXTURE_2D texture object
    void Bind() const;
};