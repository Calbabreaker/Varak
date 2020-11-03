#include "varak/renderer/renderer.h"

namespace Varak {

    void Renderer::beginScene() {}

    void Renderer::endScene() {}

    void Renderer::submit(const Ref<VertexArray>& vertexArray)
    {
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

} // namespace Varak