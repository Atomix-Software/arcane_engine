#pragma once

#include "Arcane/Render/Shader.h"
#include <glad/glad.h>

namespace Arcane
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& shaderFile);
		OpenGLShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformBool(const std::string& name, bool value) const override;

		virtual void UploadUniformInt(const std::string& name, int value) const override;
		virtual void UploadUniformInt2(const std::string& name, const glm::ivec2& value) const override;
		virtual void UploadUniformInt3(const std::string& name, const glm::ivec3& value) const override;
		virtual void UploadUniformInt4(const std::string& name, const glm::ivec4& value) const override;

		virtual void UploadUniformFloat(const std::string& name, float value) const override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const override;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& value) const override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& value) const override;

		virtual const std::string GetName() const override { return m_Name; }

		inline virtual bool operator==(Shader& other) override { return m_RendererId == static_cast<OpenGLShader&>(other).m_RendererId; }
	private:
		std::string ReadFile(const std::string& file);

		std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& srcs);

	private:
		std::string m_Name;
		uint32_t m_RendererId;

	};
}