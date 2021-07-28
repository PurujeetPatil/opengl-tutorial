#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
private:
	unsigned int m_bufferID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();
};