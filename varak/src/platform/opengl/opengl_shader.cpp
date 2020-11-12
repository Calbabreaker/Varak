#include "platform/opengl/opengl_shader.h"

#include <fstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Varak {

    OpenGLShader::OpenGLShader(const std::string& vertexSrc,
                               const std::string& fragmentSrc)
    {
        std::unordered_map<uint32_t, std::string> shaderSources;
        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        auto shaderSources = parseShader(filepath);
        compile(shaderSources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_rendererID); //
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(m_rendererID); //
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(GL_NONE); //
    }

    void OpenGLShader::setFloat1(const std::string& name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void OpenGLShader::setFloat3(const std::string& name,
                                 const glm::vec3& value)
    {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void OpenGLShader::setFloat4(const std::string& name,
                                 const glm::vec4& value)
    {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z,
                    value.w);
    }

    void OpenGLShader::setInt1(const std::string& name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE,
                           glm::value_ptr(value));
    }

    void OpenGLShader::compile(
        const std::unordered_map<uint32_t, std::string>& shaderSources)
    {
        m_rendererID = glCreateProgram();

        VR_CORE_ASSERT(shaderSources.size() <= 2,
                       "Varak only support 2 shaders at a time!");
        std::array<uint32_t, 2> shaderIDs;
        uint32_t shaderIDIndex = 0;

        for (auto const& [type, source] : shaderSources)
        {
            uint32_t shaderID = glCreateShader(type);
            const char* sourceCSTR = source.c_str();
            glShaderSource(shaderID, 1, &sourceCSTR, nullptr);
            glCompileShader(shaderID);

            // error handling
            int isCompiled = 0;
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                int length;
                glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

                std::vector<char> infoLog(length);
                glGetShaderInfoLog(shaderID, length, &length, &infoLog[0]);

                VR_CORE_ERROR("{0}", infoLog.data());
                VR_CORE_ASSERT(false, "Failed to compile shader!");
                break;
            }

            glAttachShader(m_rendererID, shaderID);
            shaderIDs[shaderIDIndex] = shaderID;
            shaderIDIndex++;
        }

        glLinkProgram(m_rendererID);

        int isLinked = 0;
        glGetProgramiv(m_rendererID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            int length;
            glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &length);

            std::vector<char> infoLog(length);
            glGetProgramInfoLog(m_rendererID, length, &length, &infoLog[0]);

            glDeleteProgram(m_rendererID);
            for (auto shaderID : shaderIDs)
                glDeleteShader(shaderID);

            VR_CORE_ERROR("{0}", infoLog.data());
            VR_CORE_ASSERT(false, "Shader failed to link!");
        }

        for (auto shaderID : shaderIDs)
        {
            glDetachShader(m_rendererID, shaderID);
            glDeleteShader(shaderID);
        }
    }

    std::unordered_map<uint32_t, std::string> OpenGLShader::parseShader(
        const std::string& filepath)
    {
        std::unordered_map<uint32_t, std::string> shaderSources;

        GLenum currentType = GL_NONE;

        std::ifstream inFile(filepath);
        std::string line;
        if (inFile)
        {
            while (std::getline(inFile, line))
            {
                if (line.find("#type") != std::string::npos)
                {
                    if (line.find("vertex") != std::string::npos)
                        currentType = GL_VERTEX_SHADER;
                    else if (line.find("fragment") != std::string::npos ||
                             line.find("pixel") != std::string::npos)
                        currentType = GL_FRAGMENT_SHADER;
                    else
                        VR_CORE_ASSERT(false, "Invalid shader type specified!");
                }
                else
                {
                    shaderSources[currentType] += line + '\n';
                }
            }
        }
        else
        {
            VR_CORE_ERROR("File does not exist at {0}", filepath);
        }

        return shaderSources;
    }

    int OpenGLShader::getUniformLocation(const std::string& name)
    {
        if (m_uniformLoactionCache.find(name) != m_uniformLoactionCache.end())
            return m_uniformLoactionCache[name];

        int location = glGetUniformLocation(m_rendererID, name.c_str());
        if (location == -1)
            VR_CORE_WARN("Uniform {0} does not apear to exist!", name);

        m_uniformLoactionCache[name] = location;
        return location;
    }

} // namespace Varak
