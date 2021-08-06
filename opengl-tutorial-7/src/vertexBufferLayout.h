#pragma once

#include <vector>
#include <GL/glew.h>
#include "errorHandler.h"

struct VertexBufferElements
{
	unsigned int type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		default:
			return 0;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElements> m_bufferLayout;
	unsigned int m_stride;
public:
	VertexBufferLayout()
		: m_stride(0) {}

	template <typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template <>
	void push<float>(unsigned int count)
	{
		m_bufferLayout.push_back({ GL_FLOAT, (unsigned int) count, GL_FALSE });
		m_stride += sizeof(GLfloat) * count;
	}

	template <>
	void push<unsigned int>(unsigned int count)
	{
		m_bufferLayout.push_back({GL_UNSIGNED_INT, (unsigned int) count, GL_FALSE});
		m_stride += sizeof(GLuint) * count;
	}

	template <>
	void push<unsigned char>(unsigned int count)
	{
		m_bufferLayout.push_back({ GL_UNSIGNED_BYTE, (unsigned int) count, GL_TRUE });
		m_stride += sizeof(GLbyte) * count;
	}

	inline const std::vector<VertexBufferElements>& getElements() const { return m_bufferLayout; }
	inline const unsigned int getStride() const { return m_stride; }

};