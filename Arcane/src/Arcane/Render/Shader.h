#pragma once

#include "Arcane/Core/Base.h"

#include <string>
#include <glm/glm.hpp>

namespace Arcane
{
	class ARC_API Shader
	{
	public:
		Shader(const std::string& vertSrc, const std::string& fragSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		bool operator==(Shader& other) { return m_RendererId == other.m_RendererId; }
	private:
		uint32_t m_RendererId;
	};
}