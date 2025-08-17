#pragma once

#include <glad/glad.h>

#include <iostream>
#include <map>

#include <glm/vec2.hpp>

class Texture {
public:
	struct SubTexture {
		glm::vec2 leftBottomUV;
		glm::vec2 rightTopUV;

		SubTexture(const glm::vec2& leftBottom, const glm::vec2& rightTop) : leftBottomUV(leftBottom), rightTopUV(rightTop) {};
		SubTexture() : leftBottomUV(0.0f), rightTopUV(1.0f) {};
	};

	Texture(
		const unsigned int width,
		const unsigned int height,
		const unsigned char* data,
		const unsigned int channels = 4,
		const GLenum filter = GL_LINEAR,
		const GLenum wrapMode = GL_CLAMP_TO_EDGE
	);
	~Texture();

	unsigned int getWidth() const { return width; };
	unsigned int getHeight() const { return height; };

	void bind() const;

	void addSubTexture(const std::string& name, const glm::vec2& leftBottom, const glm::vec2& rightTop);
	const SubTexture& getSubTexture(const std::string& name);
private:
	GLuint textureID;
	
	GLenum mode;
	unsigned int width;
	unsigned int height;

	std::map<const std::string, SubTexture> subTextures;
};