#include "headers/ResourceManager.h"

std::string ResourceManager::readShaderCode(const std::string& path) {
	std::ifstream in(path, std::ios::in);

	if (!in.is_open()) {
		std::cerr << "Can't open file: " << path << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << in.rdbuf();

	return buffer.str();
}