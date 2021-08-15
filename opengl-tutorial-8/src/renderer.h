#pragma once

#include "errorHandler.h"
#include "vertexArray.h"
#include "indexbuffer.h"
#include "shader.h"

class Renderer
{
public:
	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};