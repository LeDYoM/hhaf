#include "menuscene.hpp"
#include <haf/resources/include/resourceview.hpp>
#include <haf/resources/include/resourcehandler.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/shareddata/include/shareddataview.hpp>
#include <haf/scene_components/include/scenecontrol.hpp>

#include "../menu/mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"

using namespace mtps;
using namespace haf;
using namespace haf::scene;

namespace zoper
{

constexpr u32 PointsPerQuad = 6U;

MenuScene::MenuScene() : BaseClass{StaticTypeName}
{}
MenuScene::~MenuScene() = default;

void MenuScene::onCreated()
{
    BaseClass::onCreated();

    auto resources_loader = dataWrapper<ResourceHandler>();
    resources_loader->loadResources(MainMenuResources{});
    auto resources_viewer = dataWrapper<ResourceView>();

    createStandardBackground(this);

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
