#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"
#include "../common_scene_nodes.hpp"

#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/input/input_component.hpp>
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

    auto resources_configurator{
        dataWrapper<res::ResourcesConfigurator>()};
    resources_configurator->setResourceConfigFile("resources.txt");
    resources_configurator->loadSection("high_scores");

    auto statesController{
        component<StatesControllerComponent<HighScoresSceneStates>>()};

    normal_font_ = 
                       dataWrapper<res::ResourceRetriever>()
                       ->getTTFont(HighScoresResources::MenuFontId)
                       ->font(72);
    normal_color_   = colors::Blue;
    selected_color_ = colors::Red;

    createStandardBackground(createSceneNode<RenderizablesSceneNode>(
                                  "high_scores_main_menu_background")
                                  ->renderizableBuilder());

    auto highScoreTextController{
        createSceneNode<HighScoreTextController>("HighScoreTextController")};
    highScoreTextController->Finished.connect([this, statesController]() {
        dataWrapper<SceneControl>()->switchToNextScene();
    });
    installDebugUtils();

    statesController->start(HighScoresSceneStates::Show);
}
}  // namespace zoper
