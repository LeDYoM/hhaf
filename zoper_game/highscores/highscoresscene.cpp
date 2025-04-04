#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"
#include "../common_scene_nodes.hpp"

#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/input/input_component.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/iresource_configurator.hpp>
#include <haf/include/scene_components/iscene_control.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/scene_components/camera_component.hpp>

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

htps::str HighScores::nextSceneName()
{
    return MENU_SCENE_NAME;
}

void HighScores::onAttached()
{
    Base::onAttached();

    //    cameraComponent()->view = DefaultView;
    cameraComponent()->view = SceneBox{-0.5F, -0.5F, 1.0F, 1.0F};
    //    cameraComponent()->view = SceneBox{-0.5F, -0.5F, 1.0F, 1.0F};

    auto resources_configurator{
        attachedNode()->subSystem<res::IResourcesConfigurator>()};
    resources_configurator->setResourceConfigFile("resources.txt");
    resources_configurator->loadSection("high_scores");

    auto statesController{
        attachedNode()
            ->component<StatesControllerComponent<HighScoresSceneStates>>()};

    m_normal_font = attachedNode()
                        ->subSystem<res::IResourceRetriever>()
                        ->getTTFont(HighScoresResources::MenuFontId)
                        ->font(72);
    m_normal_color   = colors::Blue;
    m_selected_color = colors::Red;

    auto high_scores_main_menu_background{
        attachedNode()->createSceneNode("high_scores_main_menu_background")};

    createStandardBackground(high_scores_main_menu_background);

    auto highScoreTextController{
        attachedNode()
            ->createSceneNode("HighScoreTextController")
            ->component<HighScoreTextController>()};
    highScoreTextController->Finished.connect([this, statesController]() {
        attachedNode()->subSystem<ISceneControl>()->switchToNextScene();
    });
    installDebugUtils();

    statesController->start(HighScoresSceneStates::Show);
}
}  // namespace zoper
