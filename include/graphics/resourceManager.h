#pragma once

#include <glad/glad.h>

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image/stb_image.h>

#include <graphics/texture.h>
#include <graphics/shader.h>

#include "essentials.h"

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles.
class ResourceManager {
public:
    // storage
    static std::map<std::string, Texture> Textures;
    static std:: map<std::string, Shader> Shaders;
    // generates and loads a shader program from file loading vertex and fragment
    static Shader& LoadShader(const char *vShaderFile, const char *fShaderFile, const std::string &name);
    // retrieves stored shader program
    static Shader& GetShader(const std::string &name);
    // generates and loads a texture from image
    static Texture& LoadTexture(const char *file, const std::string &name, bool alpha);
    // retrieves stored texture
    static Texture& GetTexture(const std::string &name);
    // clears all loaded resources
    static void Clear();
private:
    ResourceManager() {}
    //load and generate a shader from a file
    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);
    // load single texture from image
    static Texture loadTextureFromImage(const char* image, bool alpha);
};