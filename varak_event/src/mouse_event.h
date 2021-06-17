#pragma once

#include "mouse_codes.h"
#include "event.h"

#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>

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
        MouseMovedEvent(const glm::vec2& offset) : m_offset(offset) {}

        const glm::vec2& getOffset() { return m_offset; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_offset;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseMoved)
        MAKE_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        glm::vec2 m_offset;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(const glm::vec2& offset) : m_offset(offset) {}

        const glm::vec2& getOffset() const { return m_offset; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_offset;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(MouseScrolled)
        MAKE_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        glm::vec2 m_offset;
    };

} // namespace Varak
