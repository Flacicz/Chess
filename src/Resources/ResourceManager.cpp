#include "headers/ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "./headers/stb_image.h"

ResourceManager::TextureMap ResourceManager::textures;

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

void ResourceManager::loadTexture(const std::string& name, const std::string& path) {
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!data) {
		std::cerr << "Can't load texture: " << path << std::endl;
		return;
	}

	textures.emplace(name, std::make_shared<Texture>(width, height, data, channels, GL_NEAREST, GL_CLAMP_TO_EDGE));

	stbi_image_free(data);
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& name) {
	TextureMap::const_iterator it = textures.find(name);
	if (it != textures.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the texture: " << name << std::endl;
	return nullptr;
}