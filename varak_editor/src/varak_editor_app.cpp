#include "editor_layer.h"

#include "varak_entry_point.h"

namespace Varak {

    class VarakEditor : public Application
    {
    private:
        ImGuiLayer* m_imguiLayer;

    public:
        VarakEditor() : Application("Varak Editor"), m_imguiLayer(new ImGuiLayer())
        {
            pushOverlay(m_imguiLayer); 
            pushLayer(new EditorLayer(m_imguiLayer)); 
        };

        ~VarakEditor(){};
    };

    Application* createApplication()
    {
        return new VarakEditor(); //
    }

} // namespace Varak
