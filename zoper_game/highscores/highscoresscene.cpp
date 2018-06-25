#include "highscoresscene.hpp"
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include "../highscores/highscoresdata.hpp"
#include "../highscores/highscoretextcontroller.hpp"
#include "../highscores/highscoresscenestates.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::scene::nodes;

	HighScoresScene::HighScoresScene() : BaseClass{ "HighScoresScene" } {}

	void HighScoresScene::onCreated()
	{
		BaseClass::onCreated();

        auto statesController( ensureComponentOfType<StatesController<HighScoresSceneStates>>());

		m_normalFont = resourceManager().getResource<TTFont>("menu.mainFont", "resources/oldct.ttf");
		m_normalColor = colors::Blue;
		m_selectedColor = colors::Red;
		m_normalCharacterSize = 72;

		m_resources = msptr<HighScoresResources>();
		m_resources->loadResources(resourceManager());

		m_background = createRenderizable<NodeQuad>("background");
		m_background->box = rectFromSize(2000.0f, 2000.0f);
        m_background->setTextureFill(m_resources->background);
		m_background->color = colors::White;

        auto highScoreTextController(createSceneNode<HighScoreTextController>("HishScoreTextController"));
        highScoreTextController->Finished.connect([this,statesController]() { sceneManager().terminateScene(); });

		statesController->start(HighScoresSceneStates::Show);
	}

	void HighScoresScene::updateScene()
	{
	}
}
