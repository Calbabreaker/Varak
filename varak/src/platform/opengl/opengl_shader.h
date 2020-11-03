#pragma once

#include "varak/renderer/shader.h"

namespace Varak {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc,
                     const std::string& fragmentSrc);
        ~OpenGLShader();

        void bind() override;
        void unbind() override;

    private:
        // uint32_t = GLenum
        void compile(const std::unordered_map<uint32_t, std::string>& sources);

    private:
        uint32_t m_rendererID;
    };

} // namespace Varak