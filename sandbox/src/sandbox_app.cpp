#include "example_layer.h"

#include "varak/core/entry_point.h" 

class Sandbox : public Varak::Application
{
public:
    Sandbox()
    {
        pushLayer(new ExampleLayer()); //
    };

    ~Sandbox(){};
};

Varak::Application* Varak::createApplication()
{
    return new Sandbox();
}