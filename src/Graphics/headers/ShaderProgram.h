#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

#include "../../Resources/headers/ResourceManager.h"

class ShaderProgram {
private:
	ResourceManager rm;

	GLuint programID;
public:
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~ShaderProgram();

	void createShader(const std::string& path, const GLenum shaderType, GLuint& shaderID);
	void useProgram() const;

	void setInt(const std::string& name, const GLint value) const;
};