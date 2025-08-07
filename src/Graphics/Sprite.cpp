#include "headers/Sprite.h"

Sprite::Sprite(
	std::shared_ptr<ShaderProgram> shaderProgram,
	const std::string& subTetxureName,
	std::shared_ptr<Texture> texture,
	const glm::vec2& size,
	const glm::vec2& position
) : shaderProgram(std::move(shaderProgram)), texture(std::move(texture)), size(size), position(position)
{
	GLfloat vertex_points[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
	};

	auto& subTexture = this->texture->getSubTexture(subTetxureName);

	GLfloat texture_points[] = {
		subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
		subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
		subTexture.rightTopUV.x, subTexture.rightTopUV.y,

		subTexture.rightTopUV.x, subTexture.rightTopUV.y,
		subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
		subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
	};

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_points), vertex_points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

	glGenBuffers(1, &texture_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_points), texture_points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Sprite::~Sprite() {
	glDeleteBuffers(1, &points_vbo);
	glDeleteBuffers(1, &texture_vbo);
	glDeleteVertexArrays(1, &vertexArray);
}

void Sprite::render() const {
	shaderProgram->useProgram();
	glBindVertexArray(vertexArray);

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 0.0f));

	shaderProgram->setMatrix4("modelMat", model);

	glActiveTexture(GL_TEXTURE0);
	texture->bind();

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Sprite::setSize(const glm::vec2& size) {
	this->size = size;
}

void Sprite::setPosition(const glm::vec2& position) {
	this->position = position;
}