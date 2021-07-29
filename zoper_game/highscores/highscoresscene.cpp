#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"
#include "../common_scene_nodes.hpp"

#include <haf/include/scene_components/statescontroller.hpp>
#include <haf/include/input/inputcomponent.hpp>
#include <haf/include/resources/resourceretriever.hpp>
#include <haf/include/resources/resourceconfigurator.hpp>
#include <haf/include/scene_components/scenecontrol.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/component/component_container.hpp>

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

HighScoresScene::HighScoresScene() : Scene{StaticTypeName}
{}

HighScoresScene::~HighScoresScene() = default;

htps::str HighScoresScene::nextSceneName()
{
    return MENU_SCENE_NAME;
}

void HighScoresScene::onCreated()
{
    BaseClass::onCreated();

    auto resources_configurator =
        subsystems().dataWrapper<res::ResourcesConfigurator>();
    resources_configurator->setResourceConfigFile("resources.txt");
    resources_configurator->loadSection("high_scores");

    auto statesController(
        components()
            .component<StatesController<HighScoresSceneStates>>());

    m_normalFont = subsystems()
                       .dataWrapper<res::ResourceRetriever>()
                       ->getTTFont(HighScoresResources::MenuFontId)
                       ->font(72);
    m_normalColor   = colors::Blue;
    m_selectedColor = colors::Red;

    auto renderizable_builder = createSceneNode<RenderizablesSceneNode>(
                                    "high_scores_main_menu_background")
                                    ->renderizableBuilder();

    createStandardBackground(renderizable_builder);

    auto highScoreTextController(
        createSceneNode<HighScoreTextController>("HighScoreTextController"));
    highScoreTextController->Finished.connect([this, statesController]() {
        subsystems().dataWrapper<SceneControl>()->switchToNextScene();
    });

    statesController->start(HighScoresSceneStates::Show);
}
}  // namespace zoper
