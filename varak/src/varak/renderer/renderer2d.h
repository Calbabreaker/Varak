#pragma once

#include "varak/renderer/orthographic_camera.h"
#include "varak/renderer/render_command.h"
#include "varak/renderer/shader.h"
#include "varak/renderer/texture.h"

namespace Varak {

    class Renderer2D
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        static void drawRect(const glm::vec2& position, const glm::vec2& size,
                             const glm::vec4& color = glm::vec4(1.0f));
        static void drawRect(const glm::vec3& position, const glm::vec2& size,
                             const glm::vec4& color = glm::vec4(1.0f));

        static void drawRotatedRect(const glm::vec2& position,
                                    const glm::vec2& size, float rotation,
                                    const glm::vec4& color = glm::vec4(1.0f));
        static void drawRotatedRect(const glm::vec3& position,
                                    const glm::vec2& size, float rotation,
                                    const glm::vec4& color = glm::vec4(1.0f));

        static void drawTexture(const Ref<Texture>& texture,
                                const glm::vec2& position,
                                const glm::vec2& size,
                                float tilingFactor = 1.0f,
                                const glm::vec4& tint = glm::vec4(1.0f));

        static void drawTexture(const Ref<Texture>& texture,
                                const glm::vec3& position,
                                const glm::vec2& size,
                                float tilingFactor = 1.0f,
                                const glm::vec4& tint = glm::vec4(1.0f));

        static void drawRotatedTexture(const Ref<Texture>& texture,
                                       const glm::vec2& position,
                                       const glm::vec2& size, float rotation,
                                       float tilingFactor = 1.0f,
                                       const glm::vec4& tint = glm::vec4(1.0f));
        static void drawRotatedTexture(const Ref<Texture>& texture,
                                       const glm::vec3& position,
                                       const glm::vec2& size, float rotation,
                                       float tilingFactor = 1.0f,
                                       const glm::vec4& tint = glm::vec4(1.0f));

        static void drawRect(const glm::mat4& transform,
                             const glm::vec4& color = glm::vec4(1.0f));
        static void drawTexture(const Ref<Texture>& texture,
                                const glm::mat4& transform,
                                float tilingFactor = 1.0f,
                                const glm::vec4& tint = glm::vec4(1.0f));
    };

} // namespace Varak
