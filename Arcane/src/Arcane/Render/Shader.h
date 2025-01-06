#pragma once

#include "Arcane/Core/Base.h"

#include <string>

namespace Arcane
{
	class ARC_API Shader
	{
	public:
		Shader(const std::string& vertSrc, const std::string& fragSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererId;
	};
}