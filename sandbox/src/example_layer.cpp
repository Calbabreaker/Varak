#include "example_layer.h"

using namespace Varak;

ExampleLayer::ExampleLayer()
{
}

// tempararry
#include <glad/glad.h>

void ExampleLayer::onUpdate()
{
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ExampleLayer::onImGuiRender()
{
    ImGui::Begin("test");
    ImGui::Text("hi");
    ImGui::End();
}

void ExampleLayer::onEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<KeyPressedEvent>(VR_BIND_EVENT_FUNC(ExampleLayer::onKeyPressedEvent));
}

bool ExampleLayer::onKeyPressedEvent(KeyPressedEvent& event)
{
    VR_TRACE("Key Pressed: {0}", static_cast<char>(event.getKeyCode()));
    return false;
}
