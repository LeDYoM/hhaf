#include <default_menu_paged/include/menu_paged_input_component.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::exts::dmp
{
using namespace input;

void MenuPageInputComponent::onKeyPressed(const Key& key)
{

    switch (key)
    {
        case Key::Left:
            Left();
            break;
        case Key::Right:
            Right();
            break;
        case Key::Up:
            Up();
            break;
        case Key::Down:
            Down();
            break;
        case Key::Return:
            Selected();
            break;
        default:
            break;
    }
}

}  // namespace haf::exts::dmp
