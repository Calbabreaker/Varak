#pragma once

namespace Varak {

    class Shader
    {
    public:
        static Ref<Shader> create(const std::string vertexSrc,
                                  const std::string fragmentSrc);

        virtual ~Shader() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

} // namespace Varak