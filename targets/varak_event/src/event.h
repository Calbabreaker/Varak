#pragma once

#include "varak_core.h"

#include <functional>
#include <sstream>
#include <string>

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
        EventCategoryNone =        0,
        EventCategoryWindow =      1 << 0,
        EventCategoryInput =       1 << 1,
        EventCategoryKeyboard =    1 << 2,
        EventCategoryMouse =       1 << 2,
        EventCategoryMouseButton = 1 << 3
    };
    // clang-format on

#define MAKE_EVENT_CLASS_TYPE(type)                                                                \
    static EventType getStaticType() { return EventType::type; }                                   \
    EventType getEventType() const override { return getStaticType(); }                            \
    const char* getName() const override { return #type; }

#define MAKE_EVENT_CLASS_CATEGORY(category)                                                        \
    int getCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual ~Event() = default;

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
        void dispatch(const EventFunc& func)
        {
            if (m_event.getEventType() == T::getStaticType())
                m_event.handled |= func(static_cast<T&>(m_event));
        }

    private:
        Event& m_event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.toString(); //
    }

} // namespace Varak
