#include "menuscene.hpp"
#include <haf/include/resources/resourceretriever.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/shareddata/shareddata.hpp>
#include <haf/include/scene_components/scenecontrol.hpp>

#include "mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"
#include "../static_data.hpp"
#include "../gameplay/displayvar_console.hpp"

#include <haf/include/resources/resourceconfigurator.hpp>
#include <haf/include/scene_components/scenemetrics.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene/renderizables_scenenode.hpp>
#include <haf/include/system/datawrappercreator.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::render;

namespace zoper
{

constexpr u32 PointsPerQuad = 6U;

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
    subsystems().dataWrapper<SceneMetrics>()->setViewRect(DefaultView);

    // Load the necessary resources
    auto resources_configurator =
        subsystems().dataWrapper<res::ResourcesConfigurator>();
    resources_configurator->setResourceConfigFile("resources.txt");
    resources_configurator->setResourcesDirectory("resources/");
    resources_configurator->loadSection("menu");

    auto renderizable_builder =
        createSceneNode<RenderizablesSceneNode>("main_menu_background")
            ->renderizableBuilder();
    createStandardBackground(renderizable_builder);

    auto logo =
        renderizable_builder.name("mainLogo")
            .figType(FigType_t::Quad)
            .box(Rectf32{500.f, 150.f, 1000.f, 500.f})
            .texture(
                subsystems().dataWrapper<res::ResourceRetriever>()->getTexture(
                    MainMenuResources::LogoId))
            .create();

    auto mainMenu(createSceneNode<MainMenu>(MainMenu::ClassName));

    mainMenu->MenuFinished.connect([this](const s32 status) {
        if (status == 0)
        {
            subsystems().dataWrapper<SceneControl>()->requestExit();
        }
        subsystems().dataWrapper<SceneControl>()->switchToNextScene();
    });

    auto a = createSceneNode<DisplayVarConsole>("a");
}
}  // namespace zoper
