#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Graphics/headers/ShaderProgram.h"
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

    ShaderProgram shaderProgram{ "C:/Code/C++/Chess/resources/shaders/vertex_shader.glsl",
                                 "C:/Code/C++/Chess/resources/shaders/fragment_shader.glsl" };

    ResourceManager rm{};

    rm.loadTexture("ChessDesk", "C:/Code/C++/Chess/resources/textures/ChessDesk.png");
    auto& desk = rm.getTexture("ChessDesk");
    
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

    shaderProgram.useProgram();
    shaderProgram.setInt("tex", 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.useProgram();
        glBindVertexArray(vertexArray);
        desk->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}