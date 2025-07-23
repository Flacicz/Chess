#include "headers/ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
	GLuint vs;
	if (!createShader(vertexShader, GL_VERTEX_SHADER, vs)) return;

	GLuint fs;
	if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fs)) return;

	programID = glCreateProgram();
	glAttachShader(getProgramID(), vs);
	glAttachShader(getProgramID(), fs);
	glLinkProgram(getProgramID());

	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infolog[1024];
		glGetProgramInfoLog(programID, 1024, nullptr, infolog);
		std::cerr << "Can't link shader program: " << infolog << std::endl;
	}
	else {
		is_compiled = true;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(programID);
}

void ShaderProgram::useProgram() const { glUseProgram(getProgramID()); };

bool ShaderProgram::createShader(const std::string& source,const GLenum shaderType, GLuint& shaderID) {
	shaderID = glCreateShader(shaderType);
	const char* code = source.c_str();

	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infolog[1024];
		glGetShaderInfoLog(shaderID, 1024, nullptr, infolog);
		std::cerr << "Can't compile shader: " << infolog << std::endl;
		return false;
	}

	return true;
}

void ShaderProgram::setInt(const std::string& name, const GLint value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix) const {
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

