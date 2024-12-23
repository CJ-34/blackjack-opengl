#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h>

#include <iostream>
#include <math.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "graphics/cardRenderer.h"
#include "graphics/resourceManager.h"
#include "game.h"

#include "table/deck.h"

#include "openglErrorReporting.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void setWindowIcon(GLFWwindow* window);

int main() {

    if (!glfwInit()) {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Blackjack", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        return 1;
    }


    glfwMakeContextCurrent(window);

    setWindowIcon(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    Game blackjack(window);
    blackjack.init();

    // render loop
    while(!glfwWindowShouldClose(window)) {
        // input
        glfwPollEvents();
        processInput(window);

        // rendering here
        glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        blackjack.update();

        blackjack.render();


        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void setWindowIcon(GLFWwindow* window) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load("resources/icon.png", &width, &height, &nrChannels, 0);
    if (data) {
        std::cout << "Setting window icon" << std::endl;
        GLFWimage images[1];
        images[0].width = width;
        images[0].height = height;
        images[0].pixels = data;

        glfwSetWindowIcon(window, 1, images);

        stbi_image_free(data);
    } else {
        std::cout << "Failed to load icon" << std::endl;
    }
}