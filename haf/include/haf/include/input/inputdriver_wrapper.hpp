#ifndef HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <htypes/include/types.hpp>
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

    bool arePendingKeyPresses() const;
    bool arePendingKeyReleases() const;

    Key popKeyPress();
    Key popKeyRelease();

    void keyPressed(const Key);
    void keyReleased(const Key);

private:
    htps::rptr<backend::IInputDriver> input_driver_;
};
}  // namespace haf::input

#endif
