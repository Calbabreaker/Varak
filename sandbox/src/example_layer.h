#pragma once

#include <varak.h>

class ExampleLayer : public Varak::Layer
{
public:
    ExampleLayer();

    void onUpdate() override;
    void onEvent(Varak::Event& event) override;
    bool onKeyPressedEvent(Varak::KeyPressedEvent& event);
};