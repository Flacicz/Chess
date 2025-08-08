#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Graphics/headers/ShaderProgram.h"
#include "Resources/headers/ResourceManager.h"
#include "Game/headers/Game.h"
#include "Logic/headers/Logic.h"

#include <glm/glm.hpp>

static glm::ivec2 windowSize(1420, 1080);

static void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    windowSize.x = width;
    windowSize.y = height;
    glViewport(0, 0, windowSize.x, windowSize.y);
}

static void glfwMouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        Logic::getInstance().onWhichFigureIsMouse();
    }
}

int main(void)
{
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(windowSize.x, windowSize.y, "Chess", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    Game::createInstance(windowSize);
    auto& game = Game::getInstance();

    Logic::createInstance(window);

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetMouseButtonCallback(window, glfwMouseClickCallback);

    glfwMakeContextCurrent(window);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!gladLoadGL()) {
        std::cerr << "Can't init glad" << std::endl;
    }

    glClearColor(0, 0, 0, 1);

    




    game.init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        Game::getInstance().render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}