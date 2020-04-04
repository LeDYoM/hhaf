#include <lib/input/include/inputdriver.hpp>
#include <backend_dev/include/iinputdriver.hpp>

using namespace mtps;

namespace lib::input
{
InputDriver::InputDriver(rptr<backend::IInputDriver> input_driver)
    : input_driver_{input_driver} {}

InputDriver::~InputDriver() = default;

bool InputDriver::arePendingKeyPresses() const
{
    return input_driver_->arePendingKeyPresses();
}

bool InputDriver::arePendingKeyReleases() const
{
    return input_driver_->arePendingKeyReleases();
}

Key InputDriver::popKeyPress()
{
    return input_driver_->popKeyPress();
}

Key InputDriver::popKeyRelease()
{
    return input_driver_->popKeyRelease();
}

void InputDriver::keyPressed(const Key k)
{
    return input_driver_->keyPressed(k);
}

void InputDriver::keyReleased(const Key k)
{
    return input_driver_->keyReleased(k);
}

} // namespace lib::input
