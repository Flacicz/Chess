#include "headers/Texture2D.h"

Texture2D::Texture2D(
	const GLuint width,
	const GLuint height,
	const unsigned char* data,
	const unsigned int channels,
	const GLenum filter,
	const GLenum wrapMode
) : texture_width(width), texture_height(height)
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
	glTexImage2D(GL_TEXTURE_2D, 0, mode, texture_width, texture_height, 0, mode, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
};

Texture2D& Texture2D::operator=(Texture2D&& texture2d) noexcept
{
	glDeleteTextures(1, &textureID);
	textureID = texture2d.textureID;
	texture2d.textureID = 0;
	mode = texture2d.mode;
	texture_width = texture2d.texture_width;
	texture_height = texture2d.texture_height;
	return *this;
}

Texture2D::Texture2D(Texture2D&& texture2d) noexcept
{
	textureID = texture2d.textureID;
	texture2d.textureID = 0;
	mode = texture2d.mode;
	texture_width = texture2d.texture_width;
	texture_height = texture2d.texture_height;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &textureID);
}

void Texture2D::bind() const {
	glBindTexture(GL_TEXTURE_2D, textureID);
}