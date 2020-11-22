#pragma once

#include "varak/core/key_codes.h"
#include "varak/events/event.h"

namespace Varak {

    class KeyEvent : public Event
    {
    public:
        KeyCode getKeyCode() const { return m_keyCode; }

        MAKE_EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(KeyCode keyCode) : m_keyCode(keyCode){};

        KeyCode m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(KeyCode keyCode, uint16_t repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

        uint16_t getRepeatCount() const { return m_repeatCount; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << static_cast<uint16_t>(m_keyCode) << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(KeyPressed)

    private:
        uint16_t m_repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(KeyCode keyCode) : KeyEvent(keyCode) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << static_cast<uint16_t>(m_keyCode);
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(KeyCode keyCode) : KeyEvent(keyCode) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << static_cast<uint16_t>(m_keyCode);
            return ss.str();
        }

        MAKE_EVENT_CLASS_TYPE(KeyTyped)
    };
} // namespace Varak
