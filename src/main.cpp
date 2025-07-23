#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vec2.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

#include "Render/headers/ShaderProgram.h"
#include "Render/headers/Sprite.h"
#include "Helper/headers/ChessHelper.h"

GLfloat textures[] = {
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

    auto shaderProgram = helper.loadShader("Default", "C:/Code/C++/Chess/resources/shaders/vertex_shader.txt", "C:/Code/C++/Chess/resources/shaders/fragment_shader.txt");
    if (!shaderProgram) {
        std::cerr << "Can't create shader program: " << "Default" << std::endl;
        return -1;
    }

    auto spriteProgram = helper.loadShader("SpriteShader", "C:/Code/C++/Chess/resources/shaders/vSprite.txt", "C:/Code/C++/Chess/resources/shaders/fSprite.txt");
    if (!spriteProgram) {
        std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
        return -1;
    }


    std::vector<ChessHelper::Vertex> points = helper.getPoints(squares, windowSize.x);
    std::vector<ChessHelper::Fragment> colors = helper.getColors(squares);

    helper.loadTexture("C:/Code/C++/Chess/resources/textures/figures.png");

    auto sprite = helper.loadSprite("Sprite", "White_Rook", "SpriteShader", 128, 128);
    sprite->setPosition(glm::vec2(128, 256));

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
    
    glm::mat4 projectionMat = glm::ortho(0.0f, static_cast<float>(windowSize.x), 0.0f, static_cast<float>(windowSize.y), -100.0f, 100.0f);

    spriteProgram->useProgram();
    spriteProgram->setInt("tex", 0);
    spriteProgram->setMatrix4("projectionMat", projectionMat);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram->useProgram();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, points.size());

        sprite->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}