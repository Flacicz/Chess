#include "headers/ShaderProgram.h"

ShaderProgram::ShaderProgram() {
	ChessHelper helper{};

	GLuint vs;
	if (!createShader(helper.getShaderCode(vertex_path), GL_VERTEX_SHADER, vs)) return;

	GLuint fs;
	if (!createShader(helper.getShaderCode(fragment_path), GL_FRAGMENT_SHADER, fs)) return;

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

	glDeleteShader(vs);
	glDeleteShader(fs);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(programID);
}

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

void ShaderProgram::useProgram() const { glUseProgram(getProgramID()); };








GLuint ShaderProgram::getProgramID() const { return programID; };

