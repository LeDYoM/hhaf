#ifndef HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/types/basic_types.hpp>
#include <haf/include/types/vector.hpp>
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
    explicit InputDriverWrapper(types::rptr<backend::IInputDriver> input_driver);
    ~InputDriverWrapper();

    void keyPressed(const Key);
    void keyReleased(const Key);

    void readKeyPressed(vector<Key>& keys_pressed);
    void readKeyReleased(vector<Key>& keys_released);

private:
    struct InputDriverWrapperPrivate;
    types::PImplPointer<InputDriverWrapperPrivate> p_;
};

}  // namespace haf::input

#endif
