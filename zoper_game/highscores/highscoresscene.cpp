#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"
#include "../common_scene_nodes.hpp"

#include <lib/scene/components/renderizables.hpp>
#include <lib/scene/components/inputcomponent.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/system/scenemanager.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::scene::nodes;

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
    createStandardBackground(renderizables);

    auto highScoreTextController(createSceneNode<HighScoreTextController>("HighScoreTextController"));
    highScoreTextController->Finished.connect([this, statesController]()
    {
        sceneManager().sceneController()->switchToNextScene();
    });

    statesController->start(HighScoresSceneStates::Show);
}
} // namespace zoper
