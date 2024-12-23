#pragma once

#define CARDS_PATH "../resources/cards/"
#define BACK_CARD "BACK.png"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "graphics/shader.h"
#include "graphics/texture.h"
#include "table/card.h"
#include "essentials.h"

#include <array>
#include <iostream>

class CardRenderer {
public:
    CardRenderer(Shader &shader);
    //destructor
    ~CardRenderer();

    void Draw(Texture &texture, glm::vec2 position, float rotate = 0.0f, glm::vec2 size = glm::vec2(300.0f, 450.0f), bool isCard = true);   
private:
    Shader shader;
    unsigned int VAO;
    // Initializes the buffer and the vertex attributes
    void init();
};

