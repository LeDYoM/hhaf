#include "menuscene.hpp"
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/shareddata/ishared_data.hpp>
#include <haf/include/scene_components/iscene_control.hpp>

#include "mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"
#include "../static_data.hpp"
#include <haf/include/debug_utils/displayvar_console.hpp>

#include <haf/include/resources/iresource_configurator.hpp>
#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene_nodes/renderizables_scene_node.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::render;

namespace zoper
{

MenuScene::MenuScene() : BaseClass{StaticTypeName}
{}

MenuScene::~MenuScene() = default;

str MenuScene::nextSceneName()
{
    return GAME_SCENE_NAME;
}

void MenuScene::onCreated()
{
    BaseClass::onCreated();

    // Set the default view for this scene
//    cameraComponent()->view = DefaultView;
//    cameraComponent()->view = SceneBox{0.0F, 0.0F, 5000.0F, 5000.0F};
    cameraComponent()->view = SceneBox{-0.5F, -0.5F, 1.0F, 1.0F};

    // Load the necessary resources
    auto resources_configurator{subSystem<res::IResourcesConfigurator>()};
    resources_configurator->setResourceConfigFile("resources.txt");
    resources_configurator->setResourcesDirectory("resources/");
    resources_configurator->loadSection("menu");

    // Create the background
    auto main_menu_background{
        createSceneNode<RenderizableSceneNode>("main_menu_background")};
    createStandardBackground(main_menu_background);

    // Create the logo
    auto main_menu_background_logo{
        createSceneNode<RenderizableSceneNode>("main_menu_background_logo")};
    main_menu_background_logo->prop<Position>() = vector2df{0.F, -0.28F};
    main_menu_background_logo->prop<Scale>() = vector2d{0.5F, 0.4F};
    main_menu_background_logo->renderizableBuilder()
        .name("mainLogo")
        .figType(FigType_t::Sprite)
        .texture(MainMenuResources::LogoId)
//        .shader("shader1")
        .create();

    createSceneNode<MainMenu>(MainMenu::StaticTypeName)
        ->MenuFinished.connect([this](MenuFinishedStatus const status) {
            if (status == MenuFinishedStatus::Backward)
            {
                subSystem<ISceneControl>()->requestExit();
            }
        });

    auto a = createSceneNode<DisplayVarConsole>("a");

    installDebugUtils();
}
}  // namespace zoper
