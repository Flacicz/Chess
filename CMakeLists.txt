cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

set(PROJECT_NAME Chess)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp       "src/Helper/getShader.cpp" "src/Helper/headers/getShader.h" "src/Render/ShaderProgram.cpp" "src/Render/headers/ShaderProgram.h"  )

# GLFW
add_subdirectory(libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# GLAD
add_subdirectory(libs/glad)
target_link_libraries(${PROJECT_NAME} glad)