#include "editor_layer.h"

#include "varak/core/entry_point.h"

namespace Varak {

    class VarakEditor : public Application

    {
    public:
        VarakEditor() : Application("Varak Editor")
        {
            pushLayer(new EditorLayer()); //
        };

        ~VarakEditor(){};
    };

    Application* createApplication()
    {
        return new VarakEditor(); //
    }

} // namespace Varak
