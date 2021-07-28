#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IndexBuffer
{
private:
	unsigned int m_bufferID;
	unsigned int m_count;
public:
	IndexBuffer(const void *data, unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();
};