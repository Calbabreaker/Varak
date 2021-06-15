#include "sandbox2d.h"

#include "varak/core/entry_point.h"

class Sandbox : public Varak::Application
{
public:
    Sandbox()
    {
        pushLayer(new Sandbox2D());
    };

    ~Sandbox(){};
};

Varak::Application* Varak::createApplication()
{
    return new Sandbox();
}
