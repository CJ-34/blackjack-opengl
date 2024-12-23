#include "graphics/resourceManager.h"

// #include "essentials.h"

std::map<std::string, Texture> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader& ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const std::string &name) {
    Shader shader = loadShaderFromFile(vShaderFile, fShaderFile);
    if (!shader.ID) {
        std::cerr << "Error: Failed to load shader from files: " << vShaderFile << ", " << fShaderFile << std::endl;
        // Handle error appropriately
    }
    Shaders[name] = shader;
    return Shaders[name];
}

Shader& ResourceManager::GetShader(const std::string &name) {
    if (Shaders.find(name) == Shaders.end()) {
        std::cerr << "Error: Shader not found: " << name << std::endl;
    }
    return Shaders[name];
}

Texture& ResourceManager::LoadTexture(const char *file, const std::string &name, bool alpha) {
    Texture texture = loadTextureFromImage(file, alpha);
    if (!texture.ID) {
        std::cerr << "Error: Failed to load texture from file: " << file << std::endl;
    }
    Textures[name] = texture;
    return Textures[name];
}

Texture& ResourceManager::GetTexture(const std::string &name) {
    if (Textures.find(name) == Textures.end()) {
        std::cerr << "Error: Texture not found: " << name << std::endl;
    }
    return Textures[name];
}

void ResourceManager::Clear() {
    // Properly delete all shaders and textures
    for (auto iter : Shaders) {
        glDeleteProgram(iter.second.ID);
    }
    for (auto iter : Textures) {
        glDeleteTextures(1, &iter.second.ID);
    }
    Shaders.clear();
    Textures.clear();
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile)
{
    // 1. retrieving the vertex/fragment source code from filePath

    std::string vertexCode, fragmentCode;

    try
    {
        // open shader files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // reading file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // converting to string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    // 2. creating shader from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);
    return shader;
}

Texture ResourceManager::loadTextureFromImage(const char *image, bool alpha)
{
    Texture texture{};
    if (alpha) {
        texture.internal_f = GL_RGBA;
        texture.image_f = GL_RGBA;
    }
    // loading image
    int width, height, channels;

    unsigned char *data = stbi_load(image, &width, &height, &channels, 0);

    // generating texture
    texture.Generate(width, height, data);

    return texture;
}
