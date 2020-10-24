#pragma once

#include "event.h"

namespace Varak
{
    class MouseButtonEvent : public Event
    {
    public:
        int getMouseButton() const { return m_button; }

        MAKE_EVENT_CLASS_CATEGORY(Mouse | Input | MouseButton)

    protected:
        MouseButtonEvent(int button) : m_button(button) {}

        int m_button;
    };

    class MouseButtonPressedEvent : public Event
    {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_button;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class MouseButtonReleasedEvent : public Event
    {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_button;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseButtonReleased);
    };

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

        float getX() const { return m_mouseX; }
        float getX() const { return m_mouseY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseMoved)
        MAKE_EVENT_CLASS_CATEGORY(Mouse | Input)

    private:
        float m_mouseX, m_mouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : m_xOffSet(xOffset), m_yOffset(yOffset)
        {
        }

        float getXOffset() const { return m_xOffSet; }
        float getYOfset() const { return m_yOffset; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_xOffSet << ", " << m_yOffset;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseScrolled)
        MAKE_EVENT_CLASS_CATEGORY(Mouse | Input)

    private:
        float m_xOffSet, m_yOffset;
    };
} // namespace Varak