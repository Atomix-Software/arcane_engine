#include <arcpch.h>

#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Arcane
{
    Shader::Shader(const std::string& vertSrc, const std::string& fragSrc)
    {
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* source = (const GLchar*)vertSrc.c_str();
        glShaderSource(vertex, 1, &source, NULL);
        glCompileShader(vertex);

        GLint success = 0;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            char* infoLog = (char*) malloc(1024);
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
            char* infoLog = (char*)malloc(1024);
            GLint maxLength = 0;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &maxLength);
            glGetShaderInfoLog(fragment, maxLength, &maxLength, infoLog);

            ARC_CORE_ERROR("Shader Compiler Error: {0}", infoLog);
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
            char* infoLog = (char*)malloc(1024);
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

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererId);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererId);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
    }
}