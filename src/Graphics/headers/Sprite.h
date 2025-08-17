#pragma once

#include "ShaderProgram.h"
#include "Texture.h"

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Sprite {
private:
	std::shared_ptr<ShaderProgram> shaderProgram;
	std::shared_ptr<Texture> texture;

	glm::vec2 size;
	glm::vec2 position;

	GLuint points_vbo = 0;
	GLuint texture_vbo = 0;
	GLuint vertexArray = 0;
public:
	Sprite(
		std::shared_ptr<ShaderProgram> shaderProgram,
		const std::string& subTetxureName,
		std::shared_ptr<Texture> texture,
		const glm::vec2& size = glm::vec2(1.0f),
		const glm::vec2& position = glm::vec2(0.0f)
	);
	~Sprite();

	glm::vec2 getCurrentPosition() const { return position; };
	glm::vec2 getCurrentSize() const { return size; };

	void render() const;
	void setSize(const glm::vec2& size);
	void setPosition(const glm::vec2& position);
};