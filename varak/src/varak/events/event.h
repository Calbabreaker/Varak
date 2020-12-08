#pragma once

#include <functional>
#include <sstream>
#include <string>

#include "varak/core/base.h"

namespace Varak {

    // clang-format off
    enum class EventType
    {
        None = 0,
        WindowClosed, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory 
    {
        EventCategoryNone =               0,
        EventCategoryWindow =      VR_BIT(0),
        EventCategoryInput =       VR_BIT(1),
        EventCategoryKeyboard =    VR_BIT(2),
        EventCategoryMouse =       VR_BIT(3),
        EventCategoryMouseButton = VR_BIT(4)
    };

    // clang-format on

#define MAKE_EVENT_CLASS_TYPE(type)                                                                                    \
    static EventType getStaticType() { return EventType::type; }                                                       \
    EventType getEventType() const override { return getStaticType(); }                                                \
    const char* getName() const override { return #type; }

#define MAKE_EVENT_CLASS_CATEGORY(category)                                                                            \
    int getCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual int getCategoryFlags() const = 0;
        virtual std::string toString() const { return getName(); }

        bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }

        bool handled = false;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event) : m_event(event) {}

        template <typename T, typename EventFunc>
        bool dispatch(const EventFunc& func)
        {
            if (m_event.getEventType() == T::getStaticType())
            {
                m_event.handled |= func(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }

    private:
        Event& m_event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.toString(); //
    }

} // namespace Varak
