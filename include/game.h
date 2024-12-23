#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "table/table.h"

#include "graphics/cardRenderer.h"

#include <raudio.h>

enum GameState {
    GAME_MENU,
    GAME_RUNNING,
    GAME_OVER
};

class Game {
public:
    GameState state;
    GLFWwindow* window;

    Game(GLFWwindow *window);
    ~Game();

    void init();

    void update();

    void render();

private:
    void renderHand(const Hand& hand, const glm::vec2 startPos);
    void renderDealerHand(const glm::vec2 startPos);
    void handlePlayerTurn();
    void handleDealerTurn();

    CardRenderer* Renderer;
    Table table;

    bool firstGame;

    Sound dealcardSound;
};