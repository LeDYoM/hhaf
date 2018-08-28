#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"

#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>

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

        m_normalFont = resourceManager().getResource<TTFont>
                       ("menu.mainFont")->font(72);
		m_normalColor = colors::Blue;
		m_selectedColor = colors::Red;

		m_resources = msptr<HighScoresResources>();
		m_resources->loadResources(resourceManager());

		m_background = createRenderizable<NodeQuad>("background");
		m_background->box = rectFromSize(2000.0f, 2000.0f);
        m_background->setTextureFill(resourceManager().getTexture(HighScoresResources::BackgroundTextureId));
		m_background->color = colors::White;

        auto highScoreTextController(createSceneNode<HighScoreTextController>("HighScoreTextController"));
        highScoreTextController->Finished.connect([this,statesController]() { sceneManager().terminateScene(); });

		statesController->start(HighScoresSceneStates::Show);
	}

	void HighScoresScene::updateScene()
	{
	}
}
