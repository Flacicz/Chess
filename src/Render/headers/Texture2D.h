#pragma once

#include <glad/glad.h>

class Texture2D {
private:
	GLuint textureID;
	GLuint texture_width;
	GLuint texture_height;
	GLenum mode;
public:
	Texture2D(
		const GLuint width,
		const GLuint height,
		const unsigned char* data,
		const unsigned int channels = 4,
		const GLenum filter = GL_LINEAR,
		const GLenum wrapMode = GL_CLAMP_TO_EDGE
	);

	Texture2D() = delete;
	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;
	Texture2D& operator=(Texture2D&& texture2d) noexcept;
	Texture2D(Texture2D&& texture2d) noexcept;
	~Texture2D();

	void bind() const;
};