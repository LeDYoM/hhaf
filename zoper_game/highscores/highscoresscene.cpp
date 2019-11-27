#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"

#include <lib/scene/renderizables/renderizable.hpp>
#include <lib/scene/components/renderizables.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>
#include <lib/system/resourcemanager.hpp>
#include <lib/system/systemprovider.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::scene::nodes;

constexpr u32 PointsPerQuad = 6U;

void HighScoresScene::onCreated()
{
    BaseClass::onCreated();

    auto statesController(addComponentOfType<StatesController<HighScoresSceneStates>>());
    loadResources(HighScoresResources{});
    auto resources_viewer = dataWrapper<ResourceView>();

    m_normalFont = resources_viewer->getTTFont("menu.mainFont")->font(72);
    m_normalColor = colors::Blue;
    m_selectedColor = colors::Red;

    auto renderizables = addComponentOfType<Renderizables>();
    auto background = renderizables->createNode("background");
    background->figType.set(FigType_t::Quad);
    background->pointCount.set(PointsPerQuad);
    background->box = rectFromSize(2000.0f, 2000.0f);
    background->setTextureFill(resources_viewer->getTexture(HighScoresResources::BackgroundTextureId));
    background->color = colors::White;

    auto highScoreTextController(createSceneNode<HighScoreTextController>("HighScoreTextController"));
    highScoreTextController->Finished.connect([this, statesController]()
    {
        sceneManager().sceneController()->terminateScene();
    });

    statesController->start(HighScoresSceneStates::Show);
}
} // namespace zoper
