#include "menuscene.hpp"
#include <lib/draw/nodes/nodeshape.hpp>
#include <lib/draw/nodes/nodequad.hpp>
#include <lib/draw/nodes/nodetext.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/events/inputevent.hpp>

#include "mainmenu.hpp"
#include "optionsmenu.hpp"
#include "keyredefinitionmenu.hpp"
#include "startlevelmenu.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::draw;
	using namespace lib::draw::nodes;
	using namespace lib::gui;
	using namespace zmenu;

	MenuScene::MenuScene()
		: MenuManager("MenuScene") {}

	void MenuScene::onInit()
	{
		MenuManager::onInit();
		m_background = createRenderizable<NodeQuad>("background");
		m_background->box = Rectf32::fromSize(2000.0f, 2000.0f);
		m_background->texture = host().resourceManager().getTexture("game_menu.background");
		m_background->color = colors::White;
		m_background->configure();

//		addMenuStep(msptr<MainMenuController>(this));
		addMenuStep(msptr<OptionsMenu>(this));
//		addMenuStep(msptr<KeyRedefinitionMenu>(this));
		addMenuStep(msptr<StartLevelMenu>(this));

		m_logo = createRenderizable<NodeQuad>("mainLogo");
		m_logo->box = Rectf32{ 500, 150, 1000, 500 };
		m_logo->texture = host().resourceManager().getTexture("game_menu.logo");
		m_logo->color = colors::White;
		m_logo->configure();
	}

	void MenuScene::onEnterScene()
	{
		MenuManager::onEnterScene();
//		start(MainMenu::ClassName);
	}

	void MenuScene::onExitScene()
	{
		MenuManager::onExitScene();
	}

	void MenuScene::updateScene()
	{

	}

	vector2df MenuScene::getDefaultSizeView()
	{
		return{ 2000.0f, 2000.0f };
	}
}
