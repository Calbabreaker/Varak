#pragma once

#include "camera.h"
#include "render_command.h"
#include "shader.h"

namespace Varak {

    struct SceneData
    {
        glm::mat4 viewProjection;
    };

    class Renderer
    {
    public:
        static void init();
        static void shutdown();

        static void onWindowResized(uint32_t width, uint32_t height);

        static void beginScene(const glm::mat4& viewProj);
        static void endScene();

        static void submit(const std::shared_ptr<VertexArray>& vertexArray,
                           const std::shared_ptr<Shader>& shader,
                           const glm::mat4& transform = glm::mat4(1.0f));

        static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

    private:
        inline static std::unique_ptr<SceneData> s_sceneData = std::make_unique<SceneData>();
    };

} // namespace Varak
