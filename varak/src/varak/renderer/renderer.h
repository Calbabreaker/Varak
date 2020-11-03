#pragma once

#include "varak/renderer/orthographic_camera.h"
#include "varak/renderer/render_command.h"
#include "varak/renderer/shader.h"

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

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        static void submit(const Ref<VertexArray>& vertexArray,
                           const Ref<Shader>& shader,
                           const glm::mat4& transform = glm::mat4(1.0f));

        static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

    private:
        static Scope<SceneData> s_sceneData;
    };

} // namespace Varak