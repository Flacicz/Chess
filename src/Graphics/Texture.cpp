#include "headers/Texture.h"

Texture::Texture(
	const unsigned int width,
	const unsigned int height,
	const unsigned char* data,
	const unsigned int channels,
	const GLenum filter,
	const GLenum wrapMode
) : width(width), height(height)
{
	switch (channels) {
	case 3:
		mode = GL_RGB;
		break;
	case 4:
		mode = GL_RGBA;
		break;
	default:
		mode = GL_RGBA;
		break;
	}

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::addSubTexture(const std::string& name, const glm::vec2& leftBottom, const glm::vec2& rightTop) {
	subTextures.emplace(name, SubTexture(leftBottom, rightTop));
}

const Texture::SubTexture& Texture::getSubTexture(const std::string& name) const {
	auto it = subTextures.find(name);
	if (it != subTextures.end())
	{
		return it->second;
	}
	const static SubTexture default;
	return default;
}