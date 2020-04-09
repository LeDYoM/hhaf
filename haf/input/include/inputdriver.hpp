#pragma once

#ifndef HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/input/include/key.hpp>

namespace haf::backend
{
    class IInputDriver;
}

namespace haf::input
{
class InputDriver final
{
public:
    InputDriver(mtps::rptr<backend::IInputDriver> input_driver);
    ~InputDriver();

    bool arePendingKeyPresses() const;
    bool arePendingKeyReleases() const;

    Key popKeyPress();
    Key popKeyRelease();

    void keyPressed(const Key);
    void keyReleased(const Key);

private:
    mtps::rptr<backend::IInputDriver> input_driver_;
};
} // namespace haf::backend::sfmlb

#endif
