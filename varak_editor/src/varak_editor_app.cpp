#include "editor_layer.h"

#include "varak_entry_point.h"

namespace Varak {

    class VarakEditor : public Application
    {
    public:
        VarakEditor() : Application("Varak Editor")
        {
            pushOverlay(new EditorLayer()); 
        };

        ~VarakEditor(){};
    };

    Application* createApplication()
    {
        return new VarakEditor(); //
    }

} // namespace Varak
