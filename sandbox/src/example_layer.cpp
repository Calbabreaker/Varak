#include "example_layer.h"

using namespace Varak;

ExampleLayer::ExampleLayer()
{
}

void ExampleLayer::onUpdate()
{
    if (Input::isKeyPressed(KeyCode::Enter))
    {
        VR_INFO("Enter was pressed");
    }

    if (Input::isMouseButtonPressed(MouseCode::ButtonLeft))
    {
        VR_INFO("Mouse was pressed");
    }
}

void ExampleLayer::onEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<KeyPressedEvent>(VR_BIND_EVENT_FUNC(ExampleLayer::onKeyPressedEvent));
}

bool ExampleLayer::onKeyPressedEvent(Varak::KeyPressedEvent& event)
{
    VR_TRACE("Key Pressed: {0}", static_cast<char>(event.getKeyCode()));
    return false;
}
