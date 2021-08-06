#pragma once

#include "vertexbuffer.h"
#include "vertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_rendererId;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};