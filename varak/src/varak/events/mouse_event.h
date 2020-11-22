#pragma once

#include "varak/core/mouse_codes.h"
#include "varak/events/event.h"

namespace Varak {

    class MouseButtonEvent : public Event
    {
    public:
        MouseCode getMouseButton() const { return m_button; }

        MAKE_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

    protected:
        MouseButtonEvent(MouseCode button) : m_button(button) {}

        MouseCode m_button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << static_cast<uint8_t>(m_button);
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(MouseCode button) : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << static_cast<uint8_t>(m_button);
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseButtonReleased);
    };

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

        float getX() const { return m_mouseX; }
        float getY() const { return m_mouseY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseMoved)
        MAKE_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_mouseX, m_mouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_xOffSet(xOffset), m_yOffset(yOffset) {}

        float getXOffset() const { return m_xOffSet; }
        float getYOffset() const { return m_yOffset; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_xOffSet << ", " << m_yOffset;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseScrolled)
        MAKE_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_xOffSet, m_yOffset;
    };

} // namespace Varak
