#include "headers/ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) {
	GLuint vertexShader = 0;
	this->createShader(vertexShaderCode.c_str(), GL_VERTEX_SHADER, vertexShader);

	GLuint fragmentShader = 0;
	this->createShader(fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER, fragmentShader);

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infolog[1024];
		glGetProgramInfoLog(programID, 1024, nullptr, infolog);
		std::cout << "Can't create program: " << infolog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(programID);
}

void ShaderProgram::createShader(const std::string& code,const GLenum shaderType, GLuint& shaderID) {
	const char* shaderCode = code.c_str();

	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, nullptr);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infolog[1024];
		glGetProgramInfoLog(shaderID, 1024, nullptr, infolog);
		std::cout << "Can't create shader: " << infolog << std::endl;
	}
}

void ShaderProgram::useProgram() const {
	glUseProgram(programID);
}

void ShaderProgram::setInt(const std::string& name, const GLint value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}