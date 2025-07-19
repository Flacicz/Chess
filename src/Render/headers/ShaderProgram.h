#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

#include "../../Helper/headers/chessHelper.h"

class ShaderProgram {
private:
	const char* vertex_path = "C:/Code/C++/Chess/resources/shaders/vertex_shader.txt";
	const char* fragment_path = "C:/Code/C++/Chess/resources/shaders/fragment_shader.txt";

	GLuint programID;

	bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
public:
	ShaderProgram();
	~ShaderProgram();

	void useProgram() const;
	GLuint getProgramID() const;
	void setInt(const std::string& name,const GLint value);
};