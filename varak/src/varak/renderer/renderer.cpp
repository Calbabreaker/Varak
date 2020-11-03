#include "varak/renderer/renderer.h"

namespace Varak {

    Scope<SceneData> Renderer::s_sceneData = makeScope<SceneData>();

    void Renderer::init()
    {
        RenderCommand::init(); //
    }

    void Renderer::shutdown() {}

    void Renderer::beginScene(const OrthographicCamera& camera)
    {
        s_sceneData->viewProjection = camera.getViewProjection();
    }

    void Renderer::endScene() {}

    void Renderer::submit(const Ref<VertexArray>& vertexArray,
                          const Ref<Shader>& shader, const glm::mat4& transform)
    {
        vertexArray->bind();
        shader->bind();
        shader->setMat4("u_viewProjection", s_sceneData->viewProjection);
        shader->setMat4("u_transform", transform);
        RenderCommand::drawIndexed(vertexArray);
    }

} // namespace Varak