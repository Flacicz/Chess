#pragma once

#include <glad/glad.h>

#include <iostream>

class Texture {
private:
	GLuint textureID;
	
	GLenum mode;
	unsigned int width;
	unsigned int height;
public:
	Texture(
			const unsigned int width,
		    const unsigned int height,
			const unsigned char* data,
			const unsigned int channels = 4,
			const GLenum filter = GL_LINEAR,
			const GLenum wrapMode = GL_CLAMP_TO_EDGE
	);
	~Texture();

	void bind() const;
};