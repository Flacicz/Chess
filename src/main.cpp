#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Chess", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Can't create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //GLuint VertexArrayID;
    //glGenVertexArrays(1, &VertexArrayID);
    //glBindVertexArray(VertexArrayID);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD" << std::endl;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
            3,                  // Размер
            GL_FLOAT,           // Тип
            GL_FALSE,           // Указывает, что значения не нормализованы
            0,                  // Шаг
            (void*)0            // Смещение массива в буфере
        );

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}