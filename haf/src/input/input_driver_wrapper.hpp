HTPS_PRAGMA_ONCE
#ifndef HAF_INPUT_INPUT_DRIVER_WRAPPER_INCLUDE_HPP
#define HAF_INPUT_INPUT_DRIVER_WRAPPER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/input/key.hpp>

namespace haf::backend
{
class IInputDriver;
}

namespace haf::input
{
class InputDriverWrapper final
{
public:
    explicit InputDriverWrapper(core::rptr<backend::IInputDriver> input_driver);
    ~InputDriverWrapper();

    void keyPressed(const Key);
    void keyReleased(const Key);

    void readKeyPressed(core::vector<Key>& keys_pressed);
    void readKeyReleased(core::vector<Key>& keys_released);

private:
    struct InputDriverWrapperPrivate;
    core::PImplPointer<InputDriverWrapperPrivate> p_;
};

}  // namespace haf::input

#endif
