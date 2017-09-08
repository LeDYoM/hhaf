#include "menuscene.hpp"
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/debugsystem.hpp>

#include "mainmenu.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::core;
	using namespace lib::scene;
	using namespace lib::scene::nodes;
	using namespace lib::gui;
	using namespace zmenu;

	MenuScene::MenuScene()
		: Scene{ "MenuScene" } {}

	void MenuScene::create()
	{
		Scene::create();

		mainMenuResources = msptr<MainMenuResources>();
		mainMenuResources->loadResources(resourceManager());
		m_background = createRenderizable<NodeQuad>("background");
		m_background->box = Rectf32::fromSize(2000.0f, 2000.0f);
		m_background->texture = mainMenuResources->background;
		m_background->color = colors::White;

		m_logo = createRenderizable<NodeQuad>("mainLogo");
		m_logo->box = Rectf32{ 500, 150, 1000, 500 };
		m_logo->texture = mainMenuResources->logo;
		m_logo->color = colors::White;

		auto mainMenu = createSceneNode<MainMenu>(MainMenu::ClassName);
		mainMenu->configure();
	}

	void MenuScene::onDeinit()
	{
		Scene::onDeinit();
		//		ChooseControlGroup::onExitScene();
	}

	void MenuScene::updateScene()
	{
	}
}