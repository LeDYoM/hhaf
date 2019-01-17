#pragma once

#ifndef LIB_DBACKEND_INPUTDRIVER_INCLUDE_HPP
#define LIB_DBACKEND_INPUTDRIVER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/streams.hpp>
#include <lib/include/backend/iinputdriver.hpp>
#include <queue>

namespace lib::backend::dback
{
    struct KeyEventDebug
    {
        input::Key key;
        bool pressed;
        size_type time_stamp;
    };

    class InputDriver : public IInputDriver
    {
    public:
        InputDriver();
        ~InputDriver() override = default;

        bool arePendingKeyPresses() const override;
        bool arePendingKeyReleases() const override;

        input::Key popKeyPress() override;
        input::Key popKeyRelease() override;

        void keyEvent(const sf::Event &e);

    private:
        std::queue<input::Key> m_keysPressed;
        std::queue<input::Key> m_keysReleased;
        std::queue<KeyEventDebug> key_events;

    };
}

#endif
