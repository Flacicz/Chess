cmake_minimum_required(VERSION 3.31)

set(PROJECT_NAME Chess)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp "src/Resources/headers/ResourceManager.h" "src/Resources/ResourceManager.cpp" "src/Graphics/headers/ShaderProgram.h" "src/Graphics/ShaderProgram.cpp" "src/Graphics/Texture.cpp" "src/Graphics/headers/Texture.h" "src/Resources/Figures.cpp" "src/Resources/headers/Figures.h" "src/Graphics/headers/Sprite.h" "src/Graphics/Sprite.cpp")

# GLFW
add_subdirectory(libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# GLAD
add_subdirectory(libs/glad)
target_link_libraries(${PROJECT_NAME} glad)

# GLM
add_subdirectory(libs/glm)
target_link_libraries(${PROJECT_NAME} glm)