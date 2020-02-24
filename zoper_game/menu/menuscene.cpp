#include "menuscene.hpp"
#include <lib/resources/include/resourceview.hpp>
#include <lib/resources/include/resourcehandler.hpp>
#include <lib/scene/include/scenecontroller.hpp>
#include <lib/scene/include/scenemanager.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/shareddata/include/shareddataview.hpp>

#include "../menu/mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"

namespace zoper
{
using namespace lib;
using namespace lib::scene;

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
            app<ZoperProgramController>().requestExit();
        }
        sceneManager().sceneController()->switchToNextScene();
    });
}
} // namespace zoper
