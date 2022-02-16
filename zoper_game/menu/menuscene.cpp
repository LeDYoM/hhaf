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
#include <haf/include/scene_components/iscene_metrics.hpp>
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
    cameraComponent()->view = DefaultView;
    // Load the necessary resources
    auto resources_configurator{subSystem<res::IResourcesConfigurator>()};
    resources_configurator->setResourceConfigFile("resources.txt");
    resources_configurator->setResourcesDirectory("resources/");
    resources_configurator->loadSection("menu");

    // Create the background
    auto main_menu_background{
        createSceneNode<RenderizablesSceneNode>("main_menu_background")};
    createStandardBackground(main_menu_background->renderizableBuilder());

    // Create the logo
    main_menu_background->renderizableBuilder()
        .name("mainLogo")
        .figType(FigType_t::Quad)
        .box(Rectf32{500.f, 150.f, 1000.f, 500.f})
        .texture(MainMenuResources::LogoId)
        .shader("shader1")
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
