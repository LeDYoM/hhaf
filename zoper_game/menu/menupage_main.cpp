#include "menupage_main.hpp"
#include "menupage.hpp"
#include "menupagetype.hpp"

#include <lib/include/liblog.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>

namespace zoper
{
MenuPageMain::MenuPageMain(lib::scene::SceneNode *parent, str name)
    : MenuPageSelector{parent, std::move(name)} {}

MenuPageMain::~MenuPageMain() = default;

void MenuPageMain::onCreated()
{
    BaseClass::onCreated();

    configure(
              {"Play token mode", "Play time mode", "Options", "Exit"});

    Selection.connect([this](const size_type index) {
        switch (index)
        {
        case 0:
            Forward(MenuPageType::SelectLevelToken);
            break;
        case 1:
            Forward(MenuPageType::SelectLevelSpeed);
            break;
        case 2:
            Forward(MenuPageType::Options);
            break;
        case 3:
        default:
            Back();
        }
    });
}
} // namespace zoper
