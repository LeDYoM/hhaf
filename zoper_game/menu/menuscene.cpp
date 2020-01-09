#include "menuscene.hpp"
#include <lib/scene/components/renderizables.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>
#include <lib/scene/scenecontroller.hpp>
#include <lib/resources/texture.hpp>
#include <lib/system/resourcemanager.hpp>

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

    auto logo = renderizables->createNode("mainLogo");
    logo->figType.set(FigType_t::Quad);
    logo->pointCount.set(PointsPerQuad);
    logo->box = Rectf32{500, 150, 1000, 500};
    logo->setTextureFill(resources_viewer->getTexture(MainMenuResources::LogoId));
    logo->color = colors::White;

    auto mainMenu(createSceneNode<MainMenu>(MainMenu::ClassName));
    mainMenu->MenuFinished.connect([this](const s32 status)
    {
        app<ZoperProgramController>().gameSharedData->exitGame = (status == 0);
        sceneController().terminateScene();
    });
}
} // namespace zoper
