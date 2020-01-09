#include <menu_paged/include/menu_paged_input_component.hpp>

#include <lib/include/liblog.hpp>

namespace lib::scene
{
void MenuPageInputComponent::onAttached()
{
    BaseClass::onAttached();

    KeyPressed.connect([this](const Key &key) {
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
    });
}

} // namespace lib::scene
