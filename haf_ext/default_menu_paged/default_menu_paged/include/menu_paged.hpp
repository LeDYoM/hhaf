#ifndef HAF_EXT_DEFAULT_MENU_PAGED_MAIN_INCLUDE_HPP
#define HAF_EXT_DEFAULT_MENU_PAGED_MAIN_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/events/connection.hpp>

#include <haf/include/scene/color.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/scene_components/visibility_selector_component.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_requirements.hpp>

#include <default_menu_paged/include/menu_page.hpp>
#include <default_menu_paged/include/menu_finished_status.hpp>

namespace haf::exts::dmp
{

/**
 * @brief Main class to model a menu in paged style.
 */
class MenuPaged : public component::Component
{
    using BaseClass = component::Component;

public:
    // using BaseClass::BaseClass;
    MenuPaged();

    void onAttached() override;
    ~MenuPaged() override;

    void setMenuPagedStatus(MenuFinishedStatus const status);
    MenuFinishedStatus status() const;

    void terminate(MenuFinishedStatus const status);

    evt::emitter<const MenuFinishedStatus> MenuFinished;

protected:
    htps::sptr<MenuPage> createMenuPage(htps::str name);
    void configure_menu(htps::vector_shared_pointers<MenuPage> menu_steps);
    void addRequirements(component::ComponentRequirements&) override;

private:
    htps::sptr<scene::VisibilitySelectorComponent>
        m_visibilitySelectorComponent;
    htps::sptr<scene::StatesControllerComponent<htps::s32>>
        m_statesControllerComponent;
    htps::vector_shared_pointers<MenuPage> m_menu_steps;
    MenuFinishedStatus m_status{MenuFinishedStatus::Backward};
};
}  // namespace haf::exts::dmp

#endif
