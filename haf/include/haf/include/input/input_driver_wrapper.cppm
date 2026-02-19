export module haf:input:input_driver_wrapper;

import :key;
import backend_Dev;
import :core;

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

class InputDriverWrapper final
{
public:
    explicit InputDriverWrapper(
        core::rptr<backend::IInputDriver> input_driver) :
        p_{make_pimplp<InputDriverWrapperPrivate>(input_driver)}
    {}

    ~InputDriverWrapper() = default;

    void keyPressed(Key const key)
    {
        return p_->input_driver_->keyPressed(toiKey(key));
    }

    void keyReleased(Key const key)
    {
        return p_->input_driver_->keyReleased(toiKey(key));
    }

    void readKeyPressed(core::vector<Key>& keys_pressed)
    {
        p_->input_driver_->readKeyPressed(p_->driver_keys_pressed);
        keys_pressed.clear();
        for (auto const& key : p_->driver_keys_pressed)
        {
            keys_pressed.push_back(toKey(key));
        }
    }

    void readKeyReleased(core::vector<Key>& keys_released)
    {
        p_->input_driver_->readKeyPressed(p_->driver_keys_released);
        keys_released.clear();
        for (auto const& key : p_->driver_keys_released)
        {
            keys_released.push_back(toKey(key));
        }
    }

private:
    struct InputDriverWrapperPrivate;
    core::PImplPointer<InputDriverWrapperPrivate> p_;
};

}  // namespace haf::input

#endif
