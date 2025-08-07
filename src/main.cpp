#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Graphics/headers/ShaderProgram.h"
#include "Resources/headers/ResourceManager.h"
#include "Game/headers/Game.h"

#include <glm/glm.hpp>

static glm::ivec2 windowSize(1420, 1080);

static void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    windowSize.x = width;
    windowSize.y = height;
    glViewport(0, 0, windowSize.x, windowSize.y);
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

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);

    glfwMakeContextCurrent(window);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!gladLoadGL()) {
        std::cerr << "Can't init glad" << std::endl;
    }

    glClearColor(0, 0, 0, 1);

    Game game{ windowSize };

    game.init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        game.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}