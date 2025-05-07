#include "menuscene.hpp"
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/shareddata/ishared_data.hpp>
#include <haf/include/scene_components/iscene_control.hpp>
#include <haf/include/scene_components/renderizables.hpp>

#include "mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"
#include "../static_data.hpp"

#include <haf/include/resources/iresource_configurator.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::render;
using namespace haf::exts::dmp;

namespace zoper
{

str Menu::nextSceneName()
{
    return GAME_SCENE_NAME;
}

void Menu::onAttached()
{
    Base::onAttached();

    // Load the necessary resources
    auto resources_configurator{
        attachedNode()->subSystem<res::IResourcesConfigurator>()};
    resources_configurator->setResourceConfigFile("resources.txt");
    resources_configurator->setResourcesDirectory("resources/");
    resources_configurator->loadSection("menu");

    // Create the background
    auto main_menu_background{
        attachedNode()->createSceneNode("main_menu_background")};
    createStandardBackground(main_menu_background);

    // Create the logo
    auto main_menu_background_logo_scene_node{
        attachedNode()->createSceneNode("main_menu_background_logo")};
    auto main_menu_background_logo{
        main_menu_background_logo_scene_node
            ->component<RenderizableGroupComponent>()};

    main_menu_background_logo_scene_node->Position = {0.F, -0.28F};
    main_menu_background_logo_scene_node->Scale    = {0.99F, 0.4F};
    main_menu_background_logo->renderizableBuilder()
        .name("mainLogo")
        .figType(FigType_t::Sprite)
        .texture(MainMenuResources::LogoId)
        //        .shader("shader1")
        .create();

    auto main_menu_scene_node{
        attachedNode()->createSceneNode(MainMenu::StaticTypeName)};

    main_menu_scene_node->component<MainMenu>()->MenuFinished.connect(
        [this](MenuFinishedStatus const status) {
            if (status == MenuFinishedStatus::Backward)
            {
                attachedNode()->subSystem<ISceneControl>()->requestExit();
            }
        });

    //    initDebugUtils();
}

}  // namespace zoper
