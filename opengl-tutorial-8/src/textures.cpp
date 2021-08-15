#include "textures.h"
#include "vendor/stb/stb_image.h"

Texture::Texture(const std::string& filepath)
	: m_rendererID(0), m_filepath(filepath), m_localbuffer(nullptr), m_height(0), m_width(0), m_BPP(0)
{
	/* Opengl has 0,0 coordinates at bottom left while an image has it on this top left */
	stbi_set_flip_vertically_on_load(1);

	m_localbuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	
	if (m_localbuffer)
	{
		stbi_image_free(m_localbuffer);
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
}

void Texture::bind(const unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot))
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}
