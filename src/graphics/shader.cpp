#include "graphics/shader.h"

#include "essentials.h"

Shader &Shader::Use()
{
    glUseProgram(this->ID);

    return *this;
}

void Shader::Compile(const char *vShaderSource, const char *fShaderSource)
{
    unsigned int s_vertex, s_fragment;

    s_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vertex, 1, &vShaderSource, NULL);
    glCompileShader(s_vertex);
    checkCompileErrors(s_vertex, "VERTEX");

    s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_fragment, 1, &fShaderSource, NULL);
    glCompileShader(s_fragment);
    checkCompileErrors(s_fragment, "FRAGMENT");

    this->ID = glCreateProgram();
    glAttachShader(this->ID, s_vertex);
    glAttachShader(this->ID, s_fragment);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");

    glDeleteShader(s_vertex);
    glDeleteShader(s_fragment); 
}

void Shader::SetBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int) value);
}

void Shader::SetInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &value, bool useShader)
{
    if(useShader)
        glUseProgram(this->ID);
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, false, &value[0][0]);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value, bool useShader) {
    if (useShader)
        glUseProgram(this->ID);
    glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::checkCompileErrors(unsigned int shader, const std::string &type)
    {
        int success;
        char log[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            glGetShaderInfoLog(shader, 1024, NULL, log);
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            glGetProgramInfoLog(shader, 1024, NULL, log);
        }
    }

