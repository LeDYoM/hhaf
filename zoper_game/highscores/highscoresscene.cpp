#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"
#include "../common_scene_nodes.hpp"

#include <haf/scene_components/include/statescontroller.hpp>
#include <haf/input/include/inputcomponent.hpp>
#include <haf/resources/include/iresourceretriever.hpp>
#include <haf/scene_components/include/scenecontrol.hpp>
#include <haf/resources/include/iresourceconfigurator.hpp>
#include <haf/system/include/interfaceaccess.hpp>

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

HighScoresScene::HighScoresScene() : Scene{StaticTypeName}
{}

HighScoresScene::~HighScoresScene() = default;

mtps::str HighScoresScene::nextSceneName()
{
    return MENU_SCENE_NAME;
}

void HighScoresScene::onCreated()
{
    BaseClass::onCreated();

    auto& resources_configurator =
        systemInterface<res::IResourcesConfigurator>();
    resources_configurator.setResourceConfigFile("resources.txt");
    resources_configurator.loadSection("high_scores");

    auto statesController(
        addComponentOfType<StatesController<HighScoresSceneStates>>());

    m_normalFont = systemInterface<res::IResourceRetriever>()
                       .getTTFont(HighScoresResources::MenuFontId)
                       ->font(72);
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
