#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"
#include "../common_scene_nodes.hpp"

#include <haf/include/scene_components/statescontroller.hpp>
#include <haf/include/input/inputcomponent.hpp>
#include <haf/include/resources/iresourceretriever.hpp>
#include <haf/include/scene_components/scenecontrol.hpp>
#include <haf/include/resources/iresourceconfigurator.hpp>
#include <haf/include/system/interfaceaccess.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>

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

    auto renderizable_builder = createRenderizables().renderizableBuilder();
    createStandardBackground(renderizable_builder);

    auto highScoreTextController(
        createSceneNode<HighScoreTextController>("HighScoreTextController"));
    highScoreTextController->Finished.connect([this, statesController]() {
        dataWrapper<SceneControl>()->switchToNextScene();
    });

    statesController->start(HighScoresSceneStates::Show);
}
}  // namespace zoper
