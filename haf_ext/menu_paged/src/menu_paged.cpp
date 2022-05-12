#include <menu_paged/include/menu_paged.hpp>
#include <menu_paged/include/menu_page.hpp>

#include <haf/include/component/component_container.hpp>
#include <haf/include/scene_components/iscene_control.hpp>

using namespace htps;

namespace haf::scene
{

MenuPaged::~MenuPaged() = default;

void MenuPaged::onCreated()
{
    visibilitySelectorComponent_ = component<VisibilitySelectorComponent>();
    statesControllerComponent_   = component<StatesControllerComponent<s32>>();

    statesControllerComponent_->StatePushed.connect(
        [this](const s32 menu_page) {
            visibilitySelectorComponent_->visible_index.set(
                static_cast<size_type>(menu_page));
        });

    statesControllerComponent_->StateResumed.connect(
        [this](const s32 menu_page) {
            visibilitySelectorComponent_->visible_index.set(
                static_cast<size_type>(menu_page));
        });

    statesControllerComponent_->AfterFinish.connect(
        [this]() { terminate(status_); });
}

void MenuPaged::setMenuPagedStatus(MenuFinishedStatus const status)
{
    status_ = status;
}

MenuFinishedStatus MenuPaged::status() const
{
    return status_;
}

sptr<MenuPage> MenuPaged::createMenuPage(str name)
{
    return createSceneNode<MenuPage>(htps::move(name));
}

void MenuPaged::configure_menu(
    vector_shared_pointers<scene::MenuPage> menu_steps)
{
    menu_steps_ = htps::move(menu_steps);

    for (auto&& menu_page : menu_steps_)
    {
        menu_page->Forward.connect([this](const s32 selectedIndex) {
            if (selectedIndex > -1)
            {
                statesControllerComponent_->push_state(selectedIndex);
            }
            else
            {
                statesControllerComponent_->pop_state();
            }
        });

        menu_page->Back.connect(
            [this]() { statesControllerComponent_->pop_state(); });
    }

    statesControllerComponent_->start(0);
    visibilitySelectorComponent_->visible_index.set(0U);
}

void MenuPaged::terminate(MenuFinishedStatus const status)
{
    setMenuPagedStatus(status);
    MenuFinished(status_);

    if (prop<FinishSceneAtEnd>()())
    {
        subSystem<ISceneControl>()->switchToNextScene();
    }
}

}  // namespace haf::scene
