#include "platform/opengl/opengl_shader.h"

#include <glad/glad.h>

namespace Varak {

    namespace {

        uint32_t compileShader(GLenum type, const std::string& source)
        {
            uint32_t id = glCreateShader(type);
            const char* src = source.c_str();
            glShaderSource(id, 1, &src, nullptr);
            glCompileShader(id);

            // error handling
            int result;
            glGetShaderiv(id, GL_COMPILE_STATUS, &result);
            if (result == GL_FALSE)
            {
                int length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                char* message =
                    static_cast<char*>(alloca(length * sizeof(char)));
                glGetShaderInfoLog(id, length, &length, message);

                VR_CORE_ERROR("{0}", message);
                VR_ASSERT(false, "Failed to compile shader!");
                return 0;
            }

            return id;
        }

    } // namespace

    OpenGLShader::OpenGLShader(const std::string& vertexSrc,
                               const std::string& fragmentSrc)
    {
        std::unordered_map<uint32_t, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_rendererID); //
    }

    void OpenGLShader::bind()
    {
        glUseProgram(m_rendererID); //
    }

    void OpenGLShader::unbind()
    {
        glUseProgram(0); //
    }

    void OpenGLShader::compile(
        const std::unordered_map<uint32_t, std::string> sources)
    {
        m_rendererID = glCreateProgram();

        VR_CORE_ASSERT(sources.size() <= 2,
                       "Varak only support 2 shaders at a time!");
        std::array<uint32_t, 2> shaderIDs;
        uint32_t shaderIDIndex = 0;

        for (auto& tsPair : sources)
        {
            GLenum type = tsPair.first;
            const std::string& source = tsPair.second;

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

} // namespace Varak