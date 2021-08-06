#ifndef HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/p_impl_pointer.hpp>
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
    explicit InputDriverWrapper(htps::rptr<backend::IInputDriver> input_driver);
    ~InputDriverWrapper();

    void keyPressed(const Key);
    void keyReleased(const Key);

    void readKeyPressed(htps::vector<Key>& keys_pressed);
    void readKeyReleased(htps::vector<Key>& keys_released);

private:
    struct InputDriverWrapperPrivate;
    htps::PImplPointer<InputDriverWrapperPrivate> p_;
};

}  // namespace haf::input

#endif
