#include "graphics/texture.h"

Texture::Texture()
    : ID(0), Width(0), Height(0), internal_f(GL_RGB), image_f(GL_RGB)
{
    glGenTextures(1, &this->ID);
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char *data)
{
    this->Width = width;
    this->Height = height;

    // setting texture wrap and filter mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // creating texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_f, width, height, 0, this->image_f, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // unbinding texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
