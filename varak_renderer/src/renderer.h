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

        static void submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader,
                           const glm::mat4& transform = glm::mat4(1.0f));

        static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

    private:
        static Scope<SceneData> s_sceneData;
    };

} // namespace Varak
