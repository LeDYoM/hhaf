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
	using namespace zmenu;

	MenuScene::MenuScene()
		: lib::menu::MenuManager("MenuScene") {}

	void MenuScene::onInit()
	{
		MenuManager::onInit();
		m_background = createRenderizable<NodeQuad>("background", Rectf32::fromSize( 2000.0f,2000.0f ), host().resourceManager().getTexture("game_menu.background"), colors::White);

		addMenuStep(msptr<MainMenu>(this));
		addMenuStep(msptr<OptionsMenu>(this));
//		addMenuStep(msptr<KeyRedefinitionMenu>(this));
		addMenuStep(msptr<StartLevelMenu>(this));

		m_logo = createRenderizable<NodeQuad>("mainLogo", Rectf32{ 500, 150, 1000, 500 }, host().resourceManager().getTexture("game_menu.logo"), colors::White);
	}

	void MenuScene::onEnterScene()
	{
		MenuManager::onEnterScene();
		start(MainMenu::ClassName);
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
