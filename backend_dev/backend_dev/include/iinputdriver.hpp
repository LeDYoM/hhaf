#pragma once

#ifndef LIB_BACKEND_IINPUTDRIVER_INCLUDE_HPP
#define LIB_BACKEND_IINPUTDRIVER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/key.hpp>

namespace lib::backend
{
    class IInputDriver
    {
    public:

        virtual ~IInputDriver() {}

        virtual bool arePendingKeyPresses() const = 0;
        virtual bool arePendingKeyReleases() const = 0;

        virtual input::Key popKeyPress() = 0;
        virtual input::Key popKeyRelease() = 0;

        virtual void keyPressed(const input::Key) = 0;
        virtual void keyReleased(const input::Key) = 0;
    };
}

#endif
