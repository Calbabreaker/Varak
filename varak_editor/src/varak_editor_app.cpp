#include "editor_layer.h"

#include "varak/entry_point.h"

namespace Varak {

    class VarakEditor : public Application
    {
    private:
        ImGuiLayer* m_imguiLayer;

    public:
        VarakEditor()
            : Application(WindowProperties("Varak Editor")), m_imguiLayer(new ImGuiLayer())
        {
            pushOverlay(m_imguiLayer);
            pushLayer(new EditorLayer(m_imguiLayer));
        };
    };

    Application* createApplication()
    {
        return new VarakEditor(); //
    }

} // namespace Varak
