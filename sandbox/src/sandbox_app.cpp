#include <varak.h>

class Sandbox : public Varak::Application
{
public:
    Sandbox(){};
    ~Sandbox(){};
};

Varak::Application* Varak::createApplication()
{
    return new Sandbox();
}