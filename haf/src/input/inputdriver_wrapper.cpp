#include <haf/include/input/inputdriver_wrapper.hpp>
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
InputDriverWrapper::InputDriverWrapper(rptr<backend::IInputDriver> input_driver) :
    input_driver_{input_driver}
{}

InputDriverWrapper::~InputDriverWrapper() = default;

bool InputDriverWrapper::arePendingKeyPresses() const
{
    return input_driver_->arePendingKeyPresses();
}

bool InputDriverWrapper::arePendingKeyReleases() const
{
    return input_driver_->arePendingKeyReleases();
}

Key InputDriverWrapper::popKeyPress()
{
    return toKey(input_driver_->popKeyPress());
}

Key InputDriverWrapper::popKeyRelease()
{
    return toKey(input_driver_->popKeyRelease());
}

void InputDriverWrapper::keyPressed(const Key k)
{
    return input_driver_->keyPressed(toiKey(k));
}

void InputDriverWrapper::keyReleased(const Key k)
{
    return input_driver_->keyReleased(toiKey(k));
}

}  // namespace haf::input
