#include "highscoresscene.hpp"
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include "../highscoresdata.hpp"
#include "../highscoretextcontroller.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::scene::nodes;

	HighScoresScene::HighScoresScene()
		: Scene{ "HighScoresScene" } {}

	void HighScoresScene::create()
	{
		Scene::create();

		mainMenuResources = msptr<MainMenuResources>();
		mainMenuResources->loadResources(resourceManager());

		m_background = createRenderizable<NodeQuad>("background");
		m_background->box = Rectf32::fromSize(2000.0f, 2000.0f);
		m_background->texture = mainMenuResources->background;
		m_background->color = colors::White;

		m_highScoreTextController = ensureComponentOfType<HighScoreTextController>();
		
	}

	void HighScoresScene::onDeinit()
	{
		Scene::onDeinit();
	}

	void HighScoresScene::updateScene()
	{
	}
}