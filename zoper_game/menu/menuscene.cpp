#include "menuscene.hpp"
#include <haf/resources/include/resourceview.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/shareddata/include/shareddata.hpp>
#include <haf/scene_components/include/scenecontrol.hpp>

#include "../menu/mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"

#include <haf/resources/include/iresourceconfigurator.hpp>
#include <haf/system/include/interfaceaccess.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::scene;

namespace zoper
{

constexpr u32 PointsPerQuad = 6U;

MenuScene::MenuScene() : BaseClass{StaticTypeName}
{}

MenuScene::~MenuScene() = default;

str MenuScene::nextSceneName() { return GAME_SCENE_NAME; }

void MenuScene::onCreated()
{
    BaseClass::onCreated();

    auto& resources_configurator =
        systemInterface<res::IResourcesConfigurator>();
    resources_configurator.setResourceConfigFile("resources.txt");
    resources_configurator.loadSection("menu");

    createStandardBackground(this);

    auto resources_viewer = dataWrapper<res::ResourceView>();
    auto logo =
        renderizableBuilder()
            .name("mainLogo")
            .figType(FigType_t::Quad)
            .box(Rectf32{500, 150, 1000, 500})
            .texture(resources_viewer->getTexture(MainMenuResources::LogoId))
            .create();

    auto mainMenu(createSceneNode<MainMenu>(MainMenu::ClassName));

    mainMenu->MenuFinished.connect([this](const s32 status) {
        if (status == 0)
        {
            dataWrapper<SceneControl>()->requestExit();
        }
        dataWrapper<SceneControl>()->switchToNextScene();
    });
}
}  // namespace zoper
