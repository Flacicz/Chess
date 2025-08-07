#include "headers/ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "./headers/stb_image.h"

ResourceManager::ShaderProgramMap ResourceManager::shaderPrograms;
ResourceManager::TextureMap ResourceManager::textures;
ResourceManager::SpriteMap ResourceManager::sprites;

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

std::shared_ptr<ShaderProgram> ResourceManager::loadShaderProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexShaderCode = readShaderCode(vertexPath);
	if (vertexShaderCode.empty()) std::cerr << "Can't read vertex shader" << std::endl;

	std::string fragmentShaderCode = readShaderCode(fragmentPath);
	if (fragmentShaderCode.empty()) std::cerr << "Can't read fragment shader" << std::endl;

	std::shared_ptr<ShaderProgram> shaderProgram = shaderPrograms.emplace(name, std::make_shared<ShaderProgram>(vertexShaderCode, fragmentShaderCode)).first->second;

	return shaderProgram;
}

std::shared_ptr<ShaderProgram> ResourceManager::getShaderProgram(const std::string& name) {
	ShaderProgramMap::const_iterator it = shaderPrograms.find(name);
	if (it != shaderPrograms.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the texture: " << name << std::endl;
	return nullptr;
}

void ResourceManager::loadTexture(const std::string& name, const std::string& path) {
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!data) {
		std::cerr << "Can't load texture: " << path << std::endl;
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

std::shared_ptr<Sprite> ResourceManager::loadSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderProgramName,
	const unsigned int spriteWidth,
	const unsigned int spriteHeight,
	const std::string& subTextureName)
{
	auto& texture = getTexture(textureName);
	if (!texture) std::cerr << "Can't find texture: " << textureName << std::endl;

	auto& shaderProgram = getShaderProgram(shaderProgramName);
	if (!shaderProgram) std::cerr << "Can't find texture: " << shaderProgramName << std::endl;

	std::shared_ptr<Sprite> newSprite = sprites.emplace(spriteName, std::make_shared<Sprite>(shaderProgram,
																							 subTextureName,
																							 texture,
																							 glm::vec2(spriteWidth, spriteHeight),
																							 glm::vec2(0.f, 0.f))).first->second;

	return newSprite;
}

std::shared_ptr<Sprite> ResourceManager::getSprite(const std::string& name) {
	SpriteMap::const_iterator it = sprites.find(name);
	if (it != sprites.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the sprite: " << name << std::endl;
	return nullptr;
}

std::shared_ptr<Texture> ResourceManager::loadTextureAtlas(const std::string& textureName,
														   const std::string& texturePath)
{
	auto texture = getTexture(textureName);
	if (texture) {
		unsigned int figuresCount = 15;
		unsigned int textureWidth = texture->getWidth();
		unsigned int textureHeight = texture->getHeight();

		float offsetX = (static_cast<float>(textureWidth) / figuresCount) / textureWidth;

		for (int i = 0; i < figuresCount; ++i) {
			glm::vec2 leftBottomUV(offsetX * i, 0.0f);
			glm::vec2 rightTopUV(offsetX * i + offsetX, 1.0f);
			texture->addSubTexture(Figures::convertToString(Figures::Figures(i)), leftBottomUV, rightTopUV);
		}
	}

	return texture;
}