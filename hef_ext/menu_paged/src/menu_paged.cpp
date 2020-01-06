#include <menu_paged/include/menu_paged.hpp>
#include <menu_paged/include/menu_page.hpp>

#include <lib/scene/components/statescontroller.hpp>
#include <lib/scene/components/visibility_selector.hpp>

namespace lib::scene
{

MenuPaged::~MenuPaged() = default;

void MenuPaged::setNormalTextFont(sptr<IFont> normal_text_font)
{
    normal_text_font_ = std::move(normal_text_font);
}

sptr<IFont> MenuPaged::normalTextFont() const noexcept
{
    return normal_text_font_;
}

void MenuPaged::setNormalColor(Color normal_color)
{
    normal_color_ = std::move(normal_color);
}

Color MenuPaged::normalColor() const
{
    return normal_color_;
}

void MenuPaged::setSelectedColor(Color selected_color)
{
    selected_color_ = std::move(selected_color);
}

Color MenuPaged::selectedColor() const
{
    return selected_color_;
}

void MenuPaged::setMenuPagedStatus(s32 status)
{
    status_ = status;
}

s32 MenuPaged::status() const
{
    return status_;
}

sptr<MenuPage> MenuPaged::createMenuPage(str name)
{
    return createSceneNode<MenuPage>(std::move(name));
}

void MenuPaged::configure_menu(vector_shared_pointers<scene::MenuPage> menu_steps)
{
    auto visibility_selector = addComponentOfType<VisibilitySelector>();
    auto statesController = addComponentOfType<StatesController<s32>>();
    menu_steps_ = std::move(menu_steps);

    for (auto&& menu_page : menu_steps_)
    {
        menu_page->Forward.connect([this, statesController](const s32 selectedIndex)
        {
            if (selectedIndex > -1)
            {
                statesController->push_state(selectedIndex);
            }
            else
            {
                statesController->pop_state();
            }
        });

        menu_page->Back.connect([statesController]()
        {
            statesController->pop_state();
        });
    }

    statesController->StatePushed.connect([visibility_selector](const s32 menu_page)
    {
        visibility_selector->show(static_cast<size_type>(menu_page));
    });
    
    statesController->StateResumed.connect([visibility_selector](const s32 menu_page)
    {
        visibility_selector->show(static_cast<size_type>(menu_page));
    });

    statesController->AfterFinish.connect([this]()
    {
        MenuFinished(status_);
    });
    
    statesController->start(0);
    visibility_selector->configure(0U);
}

void MenuPaged::terminate(const s32 status)
{
    setMenuPagedStatus(status);
    MenuFinished(status_);
}

}
