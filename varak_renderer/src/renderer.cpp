#include "renderer.h"
#include "renderer2d.h"

namespace Varak {

    Scope<SceneData> Renderer::s_sceneData = createScope<SceneData>();

    void Renderer::init()
    {
        VR_PROFILE_FUNCTION();

        RenderCommand::init();
        Renderer2D::init();
    }

    void Renderer::shutdown()
    {
        VR_PROFILE_FUNCTION();

        Renderer2D::shutdown();
    }

    void Renderer::onWindowResized(uint32_t width, uint32_t height)
    {
        RenderCommand::setViewport(0, 0, width, height); //
    }

    void Renderer::beginScene(const glm::mat4& viewProj)
    {
        s_sceneData->viewProjection = viewProj; //
    }

    void Renderer::endScene() {}

    void Renderer::submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
    {
        vertexArray->bind();
        shader->bind();
        shader->setMat4("u_viewProjection", s_sceneData->viewProjection);
        shader->setMat4("u_transform", transform);
        RenderCommand::drawIndexed(vertexArray);
    }

} // namespace Varak