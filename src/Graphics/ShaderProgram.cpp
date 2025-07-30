#include "headers/ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	GLuint vertexShader = 0;
	this->createShader(rm.readShaderCode(vertexShaderPath), GL_VERTEX_SHADER, vertexShader);

	GLuint fragmentShader = 0;
	this->createShader(rm.readShaderCode(fragmentShaderPath), GL_FRAGMENT_SHADER, fragmentShader);

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