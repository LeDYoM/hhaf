#include "menupageinputcomponent.hpp"

#include <lib/include/liblog.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;

void MenuPageInputComponent::onAttached()
{
    BaseClass::onAttached();

    KeyPressed.connect([this](const input::Key &key) {
        switch (key)
        {
        case input::Key::Left:
            Left();
            break;
        case input::Key::Right:
            Right();
            break;
        case input::Key::Up:
            Up();
            break;
        case input::Key::Down:
            Down();
            break;
        case input::Key::Return:
            Selected();
            break;
        default:
            break;
        }
    });
}

} // namespace zoper
