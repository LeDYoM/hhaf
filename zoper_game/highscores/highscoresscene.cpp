#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"
#include "../common_scene_nodes.hpp"

#include <lib/scene_components/include/statescontroller.hpp>
#include <lib/input/include/inputcomponent.hpp>
#include <lib/resources/include/resourceview.hpp>
#include <lib/resources/include/resourcehandler.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/scene/include/scenemanager.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::scene::nodes;

HighScoresScene::HighScoresScene() : Scene{StaticTypeName} {}
HighScoresScene::~HighScoresScene() = default;

void HighScoresScene::onCreated()
{
    BaseClass::onCreated();
    dataWrapper<ResourceHandler>()->loadResources(HighScoresResources{});

    auto statesController(addComponentOfType<StatesController<HighScoresSceneStates>>());
    auto resources_viewer = dataWrapper<ResourceView>();

    m_normalFont = resources_viewer->getTTFont("menu.mainFont")->font(72);
    m_normalColor = colors::Blue;
    m_selectedColor = colors::Red;

    createStandardBackground(this);

    auto highScoreTextController(createSceneNode<HighScoreTextController>("HighScoreTextController"));
    highScoreTextController->Finished.connect([this, statesController]()
    {
        sceneManager().sceneController()->switchToNextScene();
    });

    statesController->start(HighScoresSceneStates::Show);
}
} // namespace zoper
