#ifndef HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
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

    void readKeyPressed(htps::vector<Key>& keys_pressed) const;
    void readKeyReleased(htps::vector<Key>& keys_released) const;

private:
    htps::rptr<backend::IInputDriver> input_driver_;
    htps::vector<Key> keys_pressed_;
    htps::vector<Key> keys_released_;
};

}  // namespace haf::input

#endif
