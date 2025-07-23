#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>

class ShaderProgram {
private:
	GLuint programID;
	bool is_compiled = false;

	bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
public:
	ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	~ShaderProgram();

	bool isCompiled() const { return is_compiled; }
	GLuint ShaderProgram::getProgramID() const { return programID; };

	void useProgram() const;
	void setInt(const std::string& name,const GLint value) const;
	void setMatrix4(const std::string& name, const glm::mat4& matrix) const;
};