#pragma once

#include "varak/renderer/orthographic_camera.h"
#include "varak/renderer/render_command.h"
#include "varak/renderer/shader.h"

namespace Varak {

    class Renderer2D
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        static void drawQuad(const glm::vec2& position, const glm::vec2& size,
                             const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size,
                             const glm::vec4& color);

    };

} // namespace Varak
