#include <haf/include/input/inputdriver.hpp>
#include <backend_dev/include/iinputdriver.hpp>
#include <backend_dev/include/ikey.hpp>

using namespace htps;

namespace
{
haf::input::Key toKey(const haf::backend::IKey ikey)
{
    return static_cast<haf::input::Key>(ikey);
}

haf::backend::IKey toiKey(const haf::input::Key key)
{
    return static_cast<haf::backend::IKey>(key);
}

}  // namespace

namespace haf::input
{
InputDriver::InputDriver(rptr<backend::IInputDriver> input_driver) :
    input_driver_{input_driver}
{}

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
    return toKey(input_driver_->popKeyPress());
}

Key InputDriver::popKeyRelease()
{
    return toKey(input_driver_->popKeyRelease());
}

void InputDriver::keyPressed(const Key k)
{
    return input_driver_->keyPressed(toiKey(k));
}

void InputDriver::keyReleased(const Key k)
{
    return input_driver_->keyReleased(toiKey(k));
}

}  // namespace haf::input
