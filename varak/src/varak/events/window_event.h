#pragma once

#include "event.h"

namespace Varak
{
    class WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() = default;

        MAKE_EVENT_CLASS_TYPE(WindowClosed)
        MAKE_EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class WindowResizedEvent : public Event
    {
    public:
        WindowResizedEvent(uint32_t x, uint32_t y) : m_width(x), m_height(y) {}

        uint32_t getWidth() const { return m_width; }
        uint32_t getHeight() const { return m_height; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizedEvent: " << m_width << ", " << m_height;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(WindowResized)
        MAKE_EVENT_CLASS_CATEGORY(EventCategoryWindow)

    private:
        uint32_t m_width, m_height;
    };

    class WindowFocusEvent : public Event
    {
        MAKE_EVENT_CLASS_TYPE(WindowFocus)
        MAKE_EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class WindowLostFocusEvent : public Event
    {
        MAKE_EVENT_CLASS_TYPE(WindowLostFocus)
        MAKE_EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    class WindowMovedEvent : public Event
    {
    public:
        WindowMovedEvent(float x, float y) : m_windowX(x), m_windowY(y) {}

        float getX() const { return m_windowX; }
        float getY() const { return m_windowY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowMovedEvent: " << m_windowX << ", " << m_windowY;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(WindowMoved)
        MAKE_EVENT_CLASS_CATEGORY(EventCategoryWindow)

    private:
        float m_windowX, m_windowY;
    };

} // namespace Varak