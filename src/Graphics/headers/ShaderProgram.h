#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
private:
	GLuint programID;
public:
	ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
	~ShaderProgram();

	void createShader(const std::string& path, const GLenum shaderType, GLuint& shaderID);
	void useProgram() const;

	void setInt(const std::string& name, const GLint value) const;
	void setMatrix4(const std::string& name, const glm::mat4& value) const;
};