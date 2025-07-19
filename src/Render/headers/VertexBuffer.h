#pragma once

#include <glad/glad.h>

class VertexBuffer {
private:
	GLuint bufferID;
public:
	VertexBuffer();
	~VertexBuffer();

	void genBuffer(GLfloat* vec);
	void bind() const;
};