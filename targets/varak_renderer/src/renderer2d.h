#pragma once

#include "camera.h"
#include "render_command.h"
#include "shader.h"
#include "texture.h"

namespace Varak {

    class Renderer2D
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const glm::mat4& viewProj);
        static void endScene();

        static void startBatch();
        static void nextBatch();
        static void flush();

        static void drawRect(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f));
        static void drawTexture(const std::shared_ptr<Texture>& texture, const glm::mat4& transform,
                                float tilingFactor = 1.0f, const glm::vec4& tint = glm::vec4(1.0f));

        struct Statistics
        {
            uint32_t drawCalls;
            uint32_t quadCount;

            uint32_t getVertexCount() const { return quadCount * 4; }
            uint32_t getIndexCount() const { return quadCount * 6; }
        };

        static void resetStats();
        static const Statistics& getStats();
    };

} // namespace Varak
