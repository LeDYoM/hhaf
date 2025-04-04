#include <default_menu_paged/include/menu_paged.hpp>
#include <default_menu_paged/include/menu_page.hpp>
#include <default_menu_paged/include/menu_paged_black_board.hpp>

#include <haf/include/component/component_container.hpp>
#include <haf/include/scene_components/iscene_control.hpp>
#include <haf/include/component/component_requirements.hpp>

using namespace htps;
using namespace haf::scene;
using namespace haf::component;

namespace haf::exts::dmp
{
MenuPaged::MenuPaged()  = default;
MenuPaged::~MenuPaged() = default;

void MenuPaged::addRequirements(ComponentRequirements& c_req)
{
    c_req.component(m_visibilitySelectorComponent);
    c_req.component(m_statesControllerComponent);
}

void MenuPaged::onAttached()
{
    m_statesControllerComponent->StatePushed.connect(
        [this](s32 const menu_page) {
            m_visibilitySelectorComponent->visible_index =
                static_cast<size_type>(menu_page);
        });

    m_statesControllerComponent->StateResumed.connect(
        [this](s32 const menu_page) {
            m_visibilitySelectorComponent->visible_index =
                static_cast<size_type>(menu_page);
        });

    m_statesControllerComponent->AfterFinish.connect(
        [this]() { terminate(m_status); });
}

void MenuPaged::setMenuPagedStatus(MenuFinishedStatus const status)
{
    m_status = status;
}

MenuFinishedStatus MenuPaged::status() const
{
    return m_status;
}

sptr<MenuPage> MenuPaged::createMenuPage(str name)
{
    auto node{attachedNode()->createSceneNode(htps::move(name))};
    return node->component<MenuPage>();
}

void MenuPaged::configure_menu(vector_shared_pointers<MenuPage> menu_steps)
{
    m_menu_steps = htps::move(menu_steps);

    for (auto&& menu_page : m_menu_steps)
    {
        menu_page->Forward.connect([this](const s32 selectedIndex) {
            if (selectedIndex > -1)
            {
                m_statesControllerComponent->push_state(selectedIndex);
            }
            else
            {
                m_statesControllerComponent->pop_state();
            }
        });

        menu_page->Back.connect(
            [this]() { m_statesControllerComponent->pop_state(); });
    }

    m_statesControllerComponent->start(0);
    m_visibilitySelectorComponent->visible_index = 0U;
}

void MenuPaged::terminate(MenuFinishedStatus const status)
{
    setMenuPagedStatus(status);
    MenuFinished(m_status);

    if (attachedNode()->component<MenuPagedBlackBoard>()->FinishSceneAtEnd())
    {
        attachedNode()->subSystem<ISceneControl>()->switchToNextScene();
    }
}

}  // namespace haf::exts::dmp
