#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Render/headers/ShaderProgram.h"
#include "Render/headers/VertexArray.h"


int g_windowSizeX = 1000;
int g_windowSizeY = 1000;

static void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Chess", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Can't create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD" << std::endl;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    ChessHelper helper{};
    std::vector<ChessHelper::Vertex> points = helper.getPoints(8, g_windowSizeX);
    std::vector<ChessHelper::Fragment> colors = helper.getColors();

    ShaderProgram program{};

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(ChessHelper::Vertex), points.data(), GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(ChessHelper::Fragment), colors.data(), GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        program.useProgram();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, points.size());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}