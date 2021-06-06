#include "menuscene.hpp"
#include <haf/include/resources/iresourceretriever.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/shareddata/shareddata.hpp>
#include <haf/include/scene_components/scenecontrol.hpp>

#include "mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"
#include "../static_data.hpp"
#include "../gameplay/displayvar_console.hpp"

#include <haf/include/resources/iresourceconfigurator.hpp>
#include <haf/include/system/interfaceaccess.hpp>
#include <haf/include/scene_components/scenemetrics.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;

namespace zoper
{

constexpr u32 PointsPerQuad = 6U;

MenuScene::MenuScene() : BaseClass{StaticTypeName}
{
}

MenuScene::~MenuScene() = default;

str MenuScene::nextSceneName()
{
    return GAME_SCENE_NAME;
}

void MenuScene::onCreated()
{
    BaseClass::onCreated();

    // Set the default view for this scene
    systemInterface<ISceneMetrics>()
            .setViewRect(DefaultView);

    // Load the necessary resources
    auto& resources_configurator =
        systemInterface<res::IResourcesConfigurator>();
    resources_configurator.setResourceConfigFile("resources.txt");
    resources_configurator.setResourcesDirectory("resources/");
    resources_configurator.loadSection("menu");

    createStandardBackground(this);

    auto logo =
        renderizableBuilder()
            .name("mainLogo")
            .figType(FigType_t::Quad)
            .box(Rectf32{500.f, 150.f, 1000.f, 500.f})
            .texture(systemInterface<res::IResourceRetriever>().getTexture(
                MainMenuResources::LogoId))
            .create();

    auto mainMenu(createSceneNode<MainMenu>(MainMenu::ClassName));

    mainMenu->MenuFinished.connect([this](const s32 status) {
        if (status == 0)
        {
            dataWrapper<SceneControl>()->requestExit();
        }
        dataWrapper<SceneControl>()->switchToNextScene();
    });

    auto a = createSceneNode<DisplayVarConsole>("a");
}
}  // namespace zoper
