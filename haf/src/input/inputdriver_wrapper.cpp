#include <haf/include/input/inputdriver_wrapper.hpp>
#include <backend_dev/include/iinputdriver.hpp>
#include <backend_dev/include/ikey.hpp>

using namespace htps;

namespace
{
haf::input::Key toKey(haf::backend::IKey const ikey)
{
    return static_cast<haf::input::Key>(ikey);
}

haf::backend::IKey toiKey(haf::input::Key const key)
{
    return static_cast<haf::backend::IKey>(key);
}

}  // namespace

namespace haf::input
{
InputDriverWrapper::InputDriverWrapper(
    rptr<backend::IInputDriver> input_driver) :
    input_driver_{input_driver}
{}

InputDriverWrapper::~InputDriverWrapper() = default;

void InputDriverWrapper::readKeyPressed(htps::vector<Key>& keys_pressed) const
{
    // TODO: Optimize: We are creating the vector each time we call the function
    vector<haf::backend::IKey> driver_keys_pressed;
    input_driver_->readKeyPressed(driver_keys_pressed);
    keys_pressed.clear();
    for (auto const& key : driver_keys_pressed)
    {
        keys_pressed.push_back(toKey(key));
    }
}

void InputDriverWrapper::readKeyReleased(htps::vector<Key>& keys_released) const
{
    // TODO: Optimize: We are creating the vector each time we call the function
    vector<haf::backend::IKey> driver_keys_released;
    input_driver_->readKeyPressed(driver_keys_released);
    keys_released.clear();
    for (auto const& key : driver_keys_released)
    {
        keys_released.push_back(toKey(key));
    }
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
