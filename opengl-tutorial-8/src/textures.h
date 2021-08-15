#pragma once

#include "errorHandler.h"
#include <string>

class Texture
{
private:
	unsigned int m_rendererID;
	std::string m_filepath;
	unsigned char* m_localbuffer;
	int m_height, m_width, m_BPP; // Bytes per pixel here its 4 as in RGBA
public:
	Texture(const std::string& filepath);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int getHeight() const { return m_height; }
	inline int getWidth() const { return m_width; }
};