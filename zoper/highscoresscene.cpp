#include "highscoresscene.hpp"
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include <lib/scene/components/textselectorcontroller.hpp>

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
	}

	void HighScoresScene::onDeinit()
	{
		Scene::onDeinit();
	}

	void HighScoresScene::updateScene()
	{
	}
}