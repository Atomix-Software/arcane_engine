#pragma once

#include "Arcane/Core/Base.h"

#include <string>
#include <glm/glm.hpp>

namespace Arcane
{
	class ARC_API Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformBool(const std::string& name, bool value) const = 0;

		virtual void UploadUniformInt(const std::string& name, int value) const = 0;
		virtual void UploadUniformInt2(const std::string& name, const glm::ivec2& value) const = 0;
		virtual void UploadUniformInt3(const std::string& name, const glm::ivec3& value) const = 0;
		virtual void UploadUniformInt4(const std::string& name, const glm::ivec4& value) const = 0;

		virtual void UploadUniformFloat(const std::string& name, float value) const = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const = 0;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& value) const = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& value) const = 0;

		virtual bool operator==(Shader& other) = 0;

		static Shared<Shader> Create(const std::string& vertSrc, const std::string& fragSrc);
	};
}