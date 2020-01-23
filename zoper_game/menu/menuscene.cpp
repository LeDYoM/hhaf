#include "menuscene.hpp"
#include <lib/scene/components/renderizables.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>
#include <lib/scene/scenecontroller.hpp>
#include <lib/resources_interface/include/itexture.hpp>

#include "../menu/mainmenu.hpp"
#include "../gameshareddata.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../common_scene_nodes.hpp"

namespace zoper
{
using namespace lib;
using namespace lib::scene;

constexpr u32 PointsPerQuad = 6U;

void MenuScene::onCreated()
{
    BaseClass::onCreated();

    loadResources(MainMenuResources{});
    auto renderizables = addComponentOfType<Renderizables>();
    auto resources_viewer = dataWrapper<ResourceView>();

    createStandardBackground(renderizables);

//    auto logo = renderizables->createRenderizable(
//        "mainLogo", FigType_t::EmptyQuad, Rectf32{500, 150, 1000, 500},colors::Red);

    auto logo = renderizables->createRenderizable(
        "mainLogo", FigType_t::Quad, Rectf32{500, 150, 1000, 500},
        resources_viewer->getTexture(MainMenuResources::LogoId));

    auto mainMenu(createSceneNode<MainMenu>(MainMenu::ClassName));
    mainMenu->MenuFinished.connect([this](const s32 status)
    {
        app<ZoperProgramController>().gameSharedData->exitGame = (status == 0);
        sceneController().switchToNextScene();
    });
}
} // namespace zoper
