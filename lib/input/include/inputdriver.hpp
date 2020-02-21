#pragma once

#ifndef LIB_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define LIB_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/key.hpp>

namespace lib::backend
{
    class IInputDriver;
}

namespace lib::input
{
class InputDriver final
{
public:
    InputDriver(rptr<backend::IInputDriver> input_driver);
    ~InputDriver();

    bool arePendingKeyPresses() const;
    bool arePendingKeyReleases() const;

    Key popKeyPress();
    Key popKeyRelease();

    void keyPressed(const Key);
    void keyReleased(const Key);

private:
    rptr<backend::IInputDriver> input_driver_;
};
} // namespace lib::backend::sfmlb

#endif
