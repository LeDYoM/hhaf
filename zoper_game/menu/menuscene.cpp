#include "menuscene.hpp"
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/shareddata/shareddata.hpp>
#include <haf/include/scene_components/scenecontrol.hpp>

#include "mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"
#include "../static_data.hpp"
#include <haf/include/debug_utils/displayvar_console.hpp>

#include <haf/include/resources/iresource_configurator.hpp>
#include <haf/include/scene_components/scenemetrics.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene/renderizables_scene_node.hpp>
#include <haf/include/system/datawrappercreator.hpp>

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
    subSystem<ISceneMetrics>()->setViewRect(DefaultView);

    // Load the necessary resources
    auto resources_configurator{
        subSystem<res::IResourcesConfigurator>()};
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
        .texture(subSystem<res::IResourceRetriever>()->getTexture(
            MainMenuResources::LogoId))
        .create();

    createSceneNode<MainMenu>(MainMenu::StaticTypeName)
        ->MenuFinished.connect([this](MenuFinishedStatus const status) {
            if (status == MenuFinishedStatus::Backward)
            {
                dataWrapper<SceneControl>()->requestExit();
            }
        });

    auto a = createSceneNode<DisplayVarConsole>("a");

    installDebugUtils();
}
}  // namespace zoper
