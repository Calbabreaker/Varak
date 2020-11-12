#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "varak/core/base.h"

namespace Varak {

    class Shader
    {
    public:
        static Ref<Shader> create(const std::string& vertexSrc,
                                  const std::string& fragmentSrc);
        static Ref<Shader> create(const std::string& filepath);

        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setFloat1(const std::string& name, float value) = 0;
        virtual void setFloat3(const std::string& name,
                               const glm::vec3& value) = 0;
        virtual void setFloat4(const std::string& name,
                               const glm::vec4& value) = 0;
        virtual void setInt1(const std::string& name, int value) = 0;
        virtual void setMat4(const std::string& name,
                             const glm::mat4& value) = 0;
    };

} // namespace Varak
