#include "renderer.h"

namespace Varak {

    Scope<RendererAPI> RenderCommand::s_rendererAPI = RendererAPI::create();

} // namespace Varak
