#include "headers/VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &vao);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &vao);
}

void VertexArray::bind() const {
	glBindVertexArray(vao);
}

void VertexArray::addBuffer(const VertexBuffer& vertexBuffer) {
	bind();
	vertexBuffer.bind();
}