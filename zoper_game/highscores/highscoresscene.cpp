#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"
#include "../common_scene_nodes.hpp"

#include <haf/scene_components/include/statescontroller.hpp>
#include <haf/input/include/inputcomponent.hpp>
#include <haf/resources/include/resourceview.hpp>
#include <haf/resources/include/resourcehandler.hpp>
#include <haf/scene_components/include/scenecontrol.hpp>

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

HighScoresScene::HighScoresScene() : Scene{StaticTypeName}
{}
HighScoresScene::~HighScoresScene() = default;

void HighScoresScene::onCreated()
{
    BaseClass::onCreated();
    dataWrapper<res::ResourceHandler>()->loadResources(HighScoresResources{});

    auto statesController(
        addComponentOfType<StatesController<HighScoresSceneStates>>());
    auto resources_viewer = dataWrapper<res::ResourceView>();

    m_normalFont    = resources_viewer->getTTFont("menu.mainFont")->font(72);
    m_normalColor   = colors::Blue;
    m_selectedColor = colors::Red;

    createStandardBackground(this);

    auto highScoreTextController(
        createSceneNode<HighScoreTextController>("HighScoreTextController"));
    highScoreTextController->Finished.connect([this, statesController]() {
        dataWrapper<SceneControl>()->switchToNextScene();
    });

    statesController->start(HighScoresSceneStates::Show);
}
}  // namespace zoper
