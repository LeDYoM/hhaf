#ifndef HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_MAIN_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/connection.hpp>

#include <haf/include/scene/color.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/scene_components/visibility_selector_component.hpp>

#include "menu_page.hpp"

namespace haf::scene
{
enum class MenuFinishedStatus : htps::u8
{
    Backward,
    Forward
};

/**
 * @brief Main class to model a menu in paged style.
 */
class MenuPaged : public TransformableSceneNode
{
    using BaseClass = TransformableSceneNode;

public:
    using BaseClass::BaseClass;

    htps::PropertyState<htps::sptr<res::IFont>> NormalTextFont;
    htps::PropertyState<Color> NormalColor;
    htps::PropertyState<Color> SelectedColor;
    htps::PropertyState<bool> FinishSceneAtEnd;

    void onCreated() override;
    ~MenuPaged() override;

    void setMenuPagedStatus(MenuFinishedStatus const status);
    MenuFinishedStatus status() const;

    void terminate(MenuFinishedStatus const status);

    htps::emitter<const MenuFinishedStatus> MenuFinished;

protected:
    htps::sptr<MenuPage> createMenuPage(htps::str name);
    void configure_menu(htps::vector_shared_pointers<MenuPage> menu_steps);

private:
    htps::sptr<VisibilitySelectorComponent> visibilitySelectorComponent_;
    htps::sptr<StatesControllerComponent<htps::s32>> statesControllerComponent_;
    htps::vector_shared_pointers<MenuPage> menu_steps_;
    MenuFinishedStatus status_{MenuFinishedStatus::Backward};
};
}  // namespace haf::scene

#endif
