#include "menuscene.hpp"
#include <lib/resources/include/resourceview.hpp>
#include <lib/resources/include/resourcehandler.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/shareddata/include/shareddataview.hpp>
#include <lib/system/include/systemrequests.hpp>
#include <lib/scene_components/include/scenecontrol.hpp>

#include "../menu/mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"

using namespace mtps;
using namespace lib;
using namespace lib::scene;

namespace zoper
{

constexpr u32 PointsPerQuad = 6U;

MenuScene::MenuScene() : BaseClass{StaticTypeName} {}
MenuScene::~MenuScene() = default;

void MenuScene::onCreated()
{
    BaseClass::onCreated();

    auto resources_loader = dataWrapper<ResourceHandler>();
    resources_loader->loadResources(MainMenuResources{});
    auto resources_viewer = dataWrapper<ResourceView>();

    createStandardBackground(this);

//    auto logo = createRenderizable(
//        "mainLogo", FigType_t::EmptyQuad, Rectf32{500, 150, 1000, 500},colors::Red);

    auto logo = createRenderizable(
        "mainLogo", FigType_t::Quad, Rectf32{500, 150, 1000, 500},
        resources_viewer->getTexture(MainMenuResources::LogoId));

    auto mainMenu(createSceneNode<MainMenu>(MainMenu::ClassName));
    mainMenu->MenuFinished.connect([this](const s32 status)
    {
        if (status == 0)
        {
            dataWrapper<sys::SystemRequests>()->requestExit();
        }
        dataWrapper<SceneControl>()->switchToNextScene();
    });
}
} // namespace zoper
