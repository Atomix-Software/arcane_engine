#include <arcpch.h>

#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Arcane
{
    OpenGLShader::OpenGLShader(const std::string& vertSrc, const std::string& fragSrc)
	{
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* source = (const GLchar*)vertSrc.c_str();
        glShaderSource(vertex, 1, &source, NULL);
        glCompileShader(vertex);

        GLint success = 0;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            char* infoLog = (char*)malloc(1024);
            GLint maxLength = 0;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &maxLength);
            glGetShaderInfoLog(vertex, maxLength, &maxLength, infoLog);

            ARC_CORE_ERROR("Shader Compiler Error: {0}", infoLog);
            glDeleteShader(vertex);

            free(infoLog);
            return;
        }

        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        source = (const GLchar*)fragSrc.c_str();
        glShaderSource(fragment, 1, &source, NULL);
        glCompileShader(fragment);

        success = 0;
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            char* infoLog = (char*)malloc(1024 * 5);
            GLint maxLength = 0;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &maxLength);
            glGetShaderInfoLog(fragment, maxLength, &maxLength, infoLog);

            ARC_CORE_ERROR("Shader Compiler Error: {0}", infoLog);

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            free(infoLog);
            return;
        }

        m_RendererId = glCreateProgram();

        glAttachShader(m_RendererId, vertex);
        glAttachShader(m_RendererId, fragment);

        glLinkProgram(m_RendererId);
        glGetProgramiv(m_RendererId, GL_LINK_STATUS, &success);
        if (success == GL_FALSE)
        {
            char* infoLog = (char*)malloc(1024 * 5);
            GLint maxLength = 0;
            glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &maxLength);
            glGetProgramInfoLog(m_RendererId, maxLength, &maxLength, &infoLog[0]);

            ARC_CORE_ERROR("Shader Linking Error: {0}", infoLog);
            glDeleteProgram(m_RendererId);

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            free(infoLog);
            return;
        }

        glDetachShader(m_RendererId, vertex);
        glDetachShader(m_RendererId, fragment);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
	}

	OpenGLShader::~OpenGLShader()
	{
        glDeleteProgram(m_RendererId);
	}

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererId);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformBool(const std::string& name, bool value) const
    {
        UploadUniformInt(name, value ? GL_TRUE : GL_FALSE);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value) const
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::ivec2& value) const
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform2i(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::ivec3& value) const
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform3i(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::ivec4& value) const
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform4i(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value) const
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) const
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) const
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) const
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& value) const
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
    }
}