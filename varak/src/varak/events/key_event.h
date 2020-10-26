#pragma once

#include "event.h"

namespace Varak
{
    class KeyEvent : public Event
    {
    public:
        int getKeyCode() const { return m_keyCode; }

        MAKE_EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int keyCode) : m_keyCode(keyCode){};

        int m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode, uint16_t repeatCount)
            : KeyEvent(keyCode), m_repeatCount(repeatCount)
        {
        }

        uint16_t getRepeatCount() const { return m_repeatCount; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount
               << " repeats)";
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_keyCode;
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(KeyTyped)
    };
} // namespace Varak