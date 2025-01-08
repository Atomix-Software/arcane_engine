#include <arcpch.h>

#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Arcane
{
	/*
	* Vertex buffer
	*/

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		ARC_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		ARC_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		ARC_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererId);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		ARC_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		ARC_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/*
	* Index buffer
	*/

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) :
		m_Count(count)
	{
		ARC_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		ARC_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererId);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		ARC_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		ARC_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}