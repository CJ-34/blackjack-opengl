#include "graphics/cardRenderer.h"

CardRenderer::CardRenderer(Shader &shader) : shader(shader)
{
    this->init();
}

CardRenderer::~CardRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void CardRenderer::Draw(Texture &texture, glm::vec2 position, float rotate, glm::vec2 size, bool isCard)
{
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(1.0f * size.x, 1.0f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-1.0f * size.x, -1.0f * size.y, 0.0f));

    if (isCard) {
        model = glm::scale(model, glm::vec3(0.3f * size, 0.0f));
    } else {
        model = glm::scale(model, glm::vec3(size, 0.0f));
    }


    this->shader.SetMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void CardRenderer::init()
{
    unsigned int VBO, EBO;
    float vertices[] = {
         0.0f,  1.0f, 0.0f, 1.0f,
         0.0f,  0.0f, 0.0f, 0.0f,
         1.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  1.0f, 0.0f, 1.0f,
         1.0f,  0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}