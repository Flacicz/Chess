#include "headers/getShader.h"

std::string getShader::getShaderCode(const char* path) {
	std::ifstream shaderStream(path, std::ios::in);

	if (shaderStream.is_open()) {
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();

		shaderStream.close();

		return sstr.str();
	}
}