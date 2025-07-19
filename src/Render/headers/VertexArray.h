#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"

class VertexArray {
private:
	GLuint vao = 0;
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void addBuffer(const VertexBuffer& vertexBuffer);
};