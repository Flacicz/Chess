#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Graphics/headers/ShaderProgram.h"
#include "Resources/headers/ResourceManager.h"

#include <glm/glm.hpp>

static glm::ivec2 windowSize(1000, 1000);

GLfloat points[] = {
     -1.0f, -1.0f,
     -1.0f,  1.0f,
      1.0f,  1.0f,

      1.0f,  1.0f,
     -1.0f, -1.0f,
      1.0f, -1.0f,
};

GLfloat texture_points[] = {
      0.0f,  0.0f,
      0.0f,  1.0f,
      1.0f,  1.0f,

      1.0f,  1.0f,
      0.0f,  0.0f,
      1.0f,  0.0f,
};

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

    ResourceManager rm{};

    auto& shaderProgram = rm.loadShaderProgram("Default", "C:/Code/C++/Chess/resources/shaders/vertex_shader.txt",
                                                          "C:/Code/C++/Chess/resources/shaders/fragment_shader.txt");

    rm.loadTexture("ChessDesk", "C:/Code/C++/Chess/resources/textures/ChessDesk.png");
    rm.loadFiguresTexture("C:/Code/C++/Chess/resources/textures/Figures.png");
    
    auto& desk = rm.loadSprite("Desk", "ChessDesk", "Default", 1000, 1000);
    desk->setPosition(glm::vec2(0, 0));

    auto& sprite = rm.loadSprite("NewSprite", "BlackQueen", "Default", 125, 125);
    sprite->setPosition(glm::vec2(125, 250));
    
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint texture_vbo = 0;
    glGenBuffers(1, &texture_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture_points), texture_points, GL_STATIC_DRAW);

    GLuint vertexArray = 0;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f, static_cast<float>(windowSize.y), -100.f, 100.f);

    shaderProgram->setMatrix4("projectionMat", projectionMatrix);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vertexArray);

        desk->render();

        sprite->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}