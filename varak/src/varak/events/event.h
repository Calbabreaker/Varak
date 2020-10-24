#pragma once

#include "varak/core/base.h"

namespace Varak
{
    // clang-format off
    enum class EventType
    {
        None = 0,
        WindowClosed, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        Window =      BIT(0),
        Input =       BIT(1),
        Keyboard =    BIT(2),
        Mouse =       BIT(3),
        MouseButton = BIT(4)
    };

    // clang-format on

#define MAKE_EVENT_CLASS_TYPE(type)                                            \
    static EventType getStaticType() { return EventType::type; }               \
    EventType getEventType() const override { return getStaticType(); }        \
    const char* getName() const override { return #type; }

#define MAKE_EVENT_CLASS_CATEGORY(category)                                    \
    int getCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual int getCategoryFlags() const = 0;
        virtual std::string toString() const { return getName(); }

        bool isInCategory(EventCategory category)
        {
            return getCategoryFlags() & category;
        }

    protected:
        bool m_handled = false;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event) : m_event(event) {}

        template <typename T, typename F>
        bool dispatch(const F& func)
        {
            if (m_event.getEventType() == T::getStaticType)
            {
                m_event.m_handled |= func(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }

    private:
        Event& m_event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.toString();
    }

} // namespace Varak
