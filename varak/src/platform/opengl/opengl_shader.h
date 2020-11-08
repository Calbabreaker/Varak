#pragma once

#include "varak/renderer/shader.h"

namespace Varak {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc,
                     const std::string& fragmentSrc);
        ~OpenGLShader();

        void bind() const override;
        void unbind() const override;

        void setFloat1(const std::string& name, float value) override;
        void setFloat3(const std::string& name,
                       const glm::vec3& value) override;
        void setFloat4(const std::string& name,
                       const glm::vec4& value) override;
        void setInt1(const std::string& name, int value) override;
        void setMat4(const std::string& name, const glm::mat4& value) override;

    private:
        // uint32_t = GLenum
        void compile(const std::unordered_map<uint32_t, std::string>& sources);

        int getUniformLocation(const std::string& name);

    private:
        uint32_t m_rendererID;
        std::unordered_map<std::string, int> m_uniformLoactionCache; 
    };

} // namespace Varak
