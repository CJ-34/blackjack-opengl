#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>


class Shader {
public:
    // The program ID
    unsigned int ID;

    // default constructor
    Shader() : ID(0) {}
    // use/activate the shader
    Shader &Use();
    //
    void Compile(const char* vShaderSource, const char* fShaderSource);
    // utility uniform functions
    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetMat4(const std::string &name, const glm::mat4 &value, bool useShader = false);
    void SetVec3(const std::string &name, const glm::vec3 &value, bool useShader = false);
private:
    void checkCompileErrors(unsigned int shader, const std::string &type);
};

