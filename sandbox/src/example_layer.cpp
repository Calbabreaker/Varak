#include "example_layer.h"

ExampleLayer::ExampleLayer()
{
}

void ExampleLayer::onUpdate()
{
    VR_INFO("ExampleLayer::onUpdate");
}

void ExampleLayer::onEvent(Varak::Event& event)
{
    VR_TRACE("{0}", event);
}
