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
struct InputDriverWrapper::InputDriverWrapperPrivate
{
    rptr<backend::IInputDriver> input_driver_;
    vector<Key> keys_pressed_;
    vector<Key> keys_released_;
    vector<backend::IKey> driver_keys_pressed;
    vector<backend::IKey> driver_keys_released;

    constexpr InputDriverWrapperPrivate(
        rptr<backend::IInputDriver> input_driver) noexcept :
        input_driver_{input_driver}
    {}
};

InputDriverWrapper::InputDriverWrapper(
    rptr<backend::IInputDriver> input_driver) :
    p_{make_pimplp<InputDriverWrapperPrivate>(input_driver)}
{}

InputDriverWrapper::~InputDriverWrapper() = default;

void InputDriverWrapper::readKeyPressed(htps::vector<Key>& keys_pressed)
{
    p_->input_driver_->readKeyPressed(p_->driver_keys_pressed);
    keys_pressed.clear();
    for (auto const& key : p_->driver_keys_pressed)
    {
        keys_pressed.push_back(toKey(key));
    }
}

void InputDriverWrapper::readKeyReleased(htps::vector<Key>& keys_released)
{
    p_->input_driver_->readKeyPressed(p_->driver_keys_released);
    keys_released.clear();
    for (auto const& key : p_->driver_keys_released)
    {
        keys_released.push_back(toKey(key));
    }
}

void InputDriverWrapper::keyPressed(Key const key)
{
    return p_->input_driver_->keyPressed(toiKey(key));
}

void InputDriverWrapper::keyReleased(Key const key)
{
    return p_->input_driver_->keyReleased(toiKey(key));
}

}  // namespace haf::input
