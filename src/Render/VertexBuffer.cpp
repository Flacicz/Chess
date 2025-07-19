#include "headers/VertexBuffer.h"

VertexBuffer::VertexBuffer() {
	bufferID = 0;
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &bufferID);
}

void VertexBuffer::genBuffer(GLfloat* vec) {
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec), vec, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const {
	glBindBuffer(1, bufferID);
}