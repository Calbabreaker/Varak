#pragma once

#include "varak/core/core.h"

#include <string>

namespace Varak {

    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;
        virtual uint32_t getHandle() const = 0;

        virtual void setData(const void* data) = 0;

        virtual void bind(uint32_t slot = 0) const = 0;

        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static std::shared_ptr<Texture2D> create(const std::string& filepath);
        static std::shared_ptr<Texture2D> create(uint32_t width, uint32_t height);
    };

} // namespace Varak
