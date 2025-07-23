#include "headers/Sprite.h"

Sprite::Sprite(
	const std::shared_ptr<Texture2D> texture,
	const std::shared_ptr<ShaderProgram> ShaderProgram,
	const glm::vec2& position,
	const glm::vec2& size
) : texture(texture), shaderProgram(ShaderProgram), position(position), size(size)
{
	vao = points_vbo = texture_vbo = 0;

	const GLfloat vertexCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
	};

	const GLfloat textureCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &texture_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Sprite::~Sprite() {
	glDeleteBuffers(1, &points_vbo);
	glDeleteBuffers(1, &texture_vbo);
	glDeleteVertexArrays(1, &vao);
}

void Sprite::render() {
	shaderProgram->useProgram();

	glm::mat4 model(1.0f);

	glm::translate(model, glm::vec3(position, 0.0f));
	glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	glBindVertexArray(vao);
	shaderProgram->setMatrix4("modelMat", model);

	glActiveTexture(GL_TEXTURE0);
	texture->bind();

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}

void Sprite::setPosition(const glm::vec2& position) {
	this->position = position;
}

void Sprite::setSize(const glm::vec2& size) {
	this->size = size;
}