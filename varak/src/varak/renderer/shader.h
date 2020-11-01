#pragma once

namespace Varak {

    class Shader
    {
    public:
        static std::shared_ptr<Shader> create(const std::string vertexSrc,
                                              const std::string fragmentSrc);

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

} // namespace Varak