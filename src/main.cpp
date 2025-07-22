#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vec2.hpp>

#include <iostream>

#include "Render/headers/ShaderProgram.h"

GLfloat textures[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,

    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
};

glm::ivec2 windowSize(1024, 1024);
int squares = 8;

static void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    windowSize.x = width;
    windowSize.y = height;
    glViewport(0, 0, windowSize.x, windowSize.y);
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(windowSize.x, windowSize.y, "Chess", nullptr, nullptr);
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
    std::vector<ChessHelper::Vertex> points = helper.getPoints(squares, windowSize.x);
    std::vector<ChessHelper::Fragment> colors = helper.getColors(squares);

    helper.loadTexture("C:/Code/C++/Chess/resources/textures/figures.png");
    auto tex1 = helper.getTexture("Black_Elephant");
    auto tex2 = helper.getTexture("Black_Horse");

    ShaderProgram program{};

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(ChessHelper::Vertex), points.data(), GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(ChessHelper::Fragment), colors.data(), GL_STATIC_DRAW);

    GLuint textures_vbo = 0;
    glGenBuffers(1, &textures_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, textures_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, textures_vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    program.useProgram();
    program.setInt("tex1", 0);
    program.setInt("tex2", 1);
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        program.useProgram();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, points.size());

        tex1->bind();
        tex2->bind();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}