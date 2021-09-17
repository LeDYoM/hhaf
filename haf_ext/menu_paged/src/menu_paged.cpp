#include <menu_paged/include/menu_paged.hpp>
#include <menu_paged/include/menu_page.hpp>

#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/scene_components/visibility_selector_component.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>
#include <haf/include/component/component_container.hpp>

using namespace htps;

namespace haf::scene
{

MenuPaged::~MenuPaged() = default;

void MenuPaged::update()
{
    if (prop<SceneNodeSizeForPages>().readResetHasChanged())
    {
        auto const size{prop<SceneNodeSizeForPages>()()};
        set_property_for_each_sceneNode_as<MenuPage, SceneNodeSize>(size);
    }
}

void MenuPaged::setMenuPagedStatus(const s32 status)
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

void MenuPaged::configure_menu(
    vector_shared_pointers<scene::MenuPage> menu_steps)
{
    auto visibility_selector =
        components().component<VisibilitySelectorComponent>();
    auto statesController =
        components().component<StatesControllerComponent<s32>>();
    menu_steps_ = std::move(menu_steps);

    for (auto&& menu_page : menu_steps_)
    {
        menu_page->Forward.connect(
            [this, statesController](const s32 selectedIndex) {
                if (selectedIndex > -1)
                {
                    statesController->push_state(selectedIndex);
                }
                else
                {
                    statesController->pop_state();
                }
            });

        menu_page->Back.connect(
            [statesController]() { statesController->pop_state(); });
    }

    statesController->StatePushed.connect(
        [visibility_selector](const s32 menu_page) {
            visibility_selector->visible_index.set(
                static_cast<size_type>(menu_page));
        });

    statesController->StateResumed.connect(
        [visibility_selector](const s32 menu_page) {
            visibility_selector->visible_index.set(
                static_cast<size_type>(menu_page));
        });

    statesController->AfterFinish.connect([this]() { MenuFinished(status_); });

    statesController->start(0);
    visibility_selector->visible_index.set(0U);
}

void MenuPaged::terminate(const s32 status)
{
    setMenuPagedStatus(status);
    MenuFinished(status_);
}

}  // namespace haf::scene
