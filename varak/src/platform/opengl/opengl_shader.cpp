#include "platform/opengl/opengl_shader.h"

#include <filesystem>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

namespace Varak {

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_name(name)
    {
        VR_PROFILE_FUNCTION();

        std::unordered_map<uint32_t, std::string> shaderSources;
        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        VR_PROFILE_FUNCTION();

        auto shaderSources = parseShader(filepath);
        compile(shaderSources);

        std::filesystem::path path = filepath;
        m_name = path.stem().string();
    }

    OpenGLShader::~OpenGLShader()
    {
        VR_PROFILE_FUNCTION();

        glDeleteProgram(m_rendererID); //
    }

    void OpenGLShader::bind() const
    {
        VR_PROFILE_FUNCTION();

        glUseProgram(m_rendererID); //
    }

    void OpenGLShader::unbind() const
    {
        VR_PROFILE_FUNCTION();

        glUseProgram(GL_NONE); //
    }

    void OpenGLShader::setFloat1(const std::string& name, float value)
    {
        VR_PROFILE_FUNCTION();

        glUniform1f(getUniformLocation(name), value);
    }

    void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value)
    {
        VR_PROFILE_FUNCTION();

        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& value)
    {
        VR_PROFILE_FUNCTION();

        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::setInt1(const std::string& name, int value)
    {
        VR_PROFILE_FUNCTION();

        glUniform1i(getUniformLocation(name), value);
    }

    void OpenGLShader::setIntArray(const std::string& name, int* values, uint32_t count)
    {
        VR_PROFILE_FUNCTION();

        glUniform1iv(getUniformLocation(name), count, values);
    }

    void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value)
    {
        VR_PROFILE_FUNCTION();

        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShader::compile(const std::unordered_map<uint32_t, std::string>& shaderSources)
    {
        VR_PROFILE_FUNCTION();

        m_rendererID = glCreateProgram();

        VR_CORE_ASSERT_MSG(shaderSources.size() <= 2, "Varak only support 2 shaders at a time not {0}!",
                           shaderSources.size());
        std::array<uint32_t, 2> shaderIDs;
        uint32_t shaderIDIndex = 0;

        // go through shaders and compile
        for (auto const& [type, source] : shaderSources)
        {
            uint32_t shaderID = glCreateShader(type);
            const char* sourceCSTR = source.c_str();
            glShaderSource(shaderID, 1, &sourceCSTR, nullptr);
            glCompileShader(shaderID);

            int isCompiled = 0;
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                // no need to get error because error callback will be called
                // with error message anyways

                VR_CORE_ASSERT_MSG(false, "Failed to compile a shader in '{0}' shader!", m_name);
                break;
            }

            glAttachShader(m_rendererID, shaderID);
            shaderIDs[shaderIDIndex] = shaderID;
            shaderIDIndex++;
        }

        // link program
        glLinkProgram(m_rendererID);

        int isLinked = 0;
        glGetProgramiv(m_rendererID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            glDeleteProgram(m_rendererID);
            for (auto shaderID : shaderIDs)
                glDeleteShader(shaderID);

            VR_CORE_ASSERT_MSG(false, "Failed to link '{0}' shader!", m_name);
        }

        for (auto shaderID : shaderIDs)
        {
            glDetachShader(m_rendererID, shaderID);
            glDeleteShader(shaderID);
        }
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::parseShader(const std::string& filepath)
    {
        VR_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shaderSources;

        GLenum currentType = GL_NONE;

        std::ifstream inFile(filepath);
        std::string line;
        if (inFile)
        {
            while (std::getline(inFile, line))
            {
                // is a shader type declaration
                if (line.find("#type") != std::string::npos)
                {
                    // get the type
                    if (line.find("vertex") != std::string::npos)
                        currentType = GL_VERTEX_SHADER;
                    else if (line.find("fragment") != std::string::npos || line.find("pixel") != std::string::npos)
                        currentType = GL_FRAGMENT_SHADER;
                    else
                        VR_CORE_ASSERT_MSG(false, "Invalid shader type specified!");
                }
                else if (currentType != GL_NONE)
                {
                    std::string& source = shaderSources[currentType];
                    source += line;
                    source += '\n';
                }
            }
        }
        else
        {
            VR_CORE_ASSERT_MSG(false, "File does not exist at {0}!", filepath);
        }

        return shaderSources;
    }

    int OpenGLShader::getUniformLocation(const std::string& name)
    {
        VR_PROFILE_FUNCTION();

        if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
            return m_uniformLocationCache[name];

        int location = glGetUniformLocation(m_rendererID, name.c_str());
        if (location == -1)
            VR_CORE_WARN("Uniform {0} does not apear to exist!", name);

        m_uniformLocationCache[name] = location;
        return location;
    }

} // namespace Varak
