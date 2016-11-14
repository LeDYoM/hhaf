#include "menuscene.hpp"
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
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
	using namespace zmenu;

	MenuScene::MenuScene()
		: lib::menu::MenuManager("MenuScene")
	{
	}


	MenuScene::~MenuScene()
	{
	}

	void MenuScene::onInit()
	{
		MenuManager::onInit();
		_background = createSpriteShape("background");

		addMenuStep(msptr<MainMenu>(this));
		addMenuStep(msptr<OptionsMenu>(this));
//		addMenuStep(msptr<KeyRedefinitionMenu>(this));
		addMenuStep(msptr<StartLevelMenu>(this));

		_logo = createSpriteShape("mainLogo");
		_logo->setTexture(lib::host().resourceManager().getResource("game_menu.logo")->getAsTexture(), true, false);
		_logo->setSize(sf::Vector2f(800, 400));
		_logo->setPositionX(getCenterCoordinates().x, lib::draw::Alignment::Center);
		_logo->setPositionY(100);

		_background->setTexture(lib::host().resourceManager().getResource("game_menu.background")->getAsTexture(), true, false);
		_background->setSize(2000.0f);
	}

	void MenuScene::onEnterScene()
	{
		MenuManager::onEnterScene();
		start(StartLevelMenu::ClassName);
	}

	void MenuScene::onExitScene()
	{
		lib::menu::MenuManager::onExitScene();
	}

	void MenuScene::update()
	{

	}

	const lib::vector2df MenuScene::getDefaultSizeView()
	{
		return{ 2000.0f, 2000.0f };
	}
}
