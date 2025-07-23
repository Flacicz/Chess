#pragma once

#include <memory>

#include "Texture2D.h"
#include "ShaderProgram.h"

#include "vec2.hpp"
#include "mat4x4.hpp"
#include "gtc/matrix_transform.hpp"

class Sprite {
private:
	std::shared_ptr<Texture2D> texture;
	std::shared_ptr<ShaderProgram> shaderProgram;
	glm::vec2 position;
	glm::vec2 size;

	GLuint vao;
	GLuint points_vbo;
	GLuint texture_vbo;
public:
	Sprite(
		const std::shared_ptr<Texture2D> texture,
		const std::shared_ptr<ShaderProgram> ShaderProgram,
		const glm::vec2& position,
		const glm::vec2& size
	);
	~Sprite();

	void render();
	void setPosition(const glm::vec2& pos);
	void setSize(const glm::vec2& position);

};