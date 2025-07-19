cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

set(PROJECT_NAME Chess)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
				src/main.cpp
				"src/Helper/ChessHelper.cpp"
				"src/Helper/headers/ChessHelper.h"
				"src/Render/ShaderProgram.cpp"
				"src/Render/headers/ShaderProgram.h"
				"src/Render/VertexArray.cpp"
				"src/Render/headers/VertexArray.h"
				"src/Render/headers/VertexBuffer.h"
				"src/Render/VertexBuffer.cpp"
				"src/Helper/headers/stb_image.h"
				"src/Render/Texture2D.cpp"
				"src/Render/headers/Texture2D.h"
)

# GLFW
add_subdirectory(libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# GLAD
add_subdirectory(libs/glad)
target_link_libraries(${PROJECT_NAME} glad)