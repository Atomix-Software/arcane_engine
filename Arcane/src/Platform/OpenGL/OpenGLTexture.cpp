#include <arcpch.h>

#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Arcane
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
		m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		ARC_CORE_ASSERT(data, "Failed to load image!");

		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		int channelBit = channels > 3 ? GL_RGBA8 : GL_RGB8;
		glTextureStorage2D(m_RendererID, 1, channelBit, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		channelBit = channels > 3 ? GL_RGBA : GL_RGB;
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, channelBit, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}