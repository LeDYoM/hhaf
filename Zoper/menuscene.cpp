#include "menuscene.hpp"
#include "lib/scn/draw/renderizable.hpp"
#include "lib/scn/resourcemanager.hpp"
#include "lib/scn/resource.hpp"

#include "mainmenu.hpp"
#include "optionsmenu.hpp"
#include "keyredefinitionmenu.hpp"
#include "startlevelmenu.hpp"

namespace zoper
{
	MenuScene::MenuScene()
		: lib::menu::MenuManager("MenuScene")
	{
	}


	MenuScene::~MenuScene()
	{
	}

	void MenuScene::onInit()
	{
		addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::MainMenu));
		addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::OptionsMenu));
		addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::KeyRedefinitionMenu));
		addMenuStep(lib::sptr<lib::menu::MenuStep>(new zoper::zmenu::StartLevelMenu));

		_logo = createSpriteShape("mainLogo");
		auto _logoSprite = _logo->getAsEllipseShape();
		_logoSprite->setTexture(resourceManager()->getResource("game_menu.logo")->getAsTexture(), true, false);
		_logoSprite->setSize(sf::Vector2f(800, 400));
		_logo->setPositionX(getCenterCoordinates().x, lib::scn::draw::Alignment::Center);
		_logo->setPositionY(100);
	}

	void MenuScene::onDeinit()
	{

	}

	void MenuScene::onEnterScene()
	{
		start("MainMenu");
	}

	void MenuScene::onExitScene()
	{
	}

	void MenuScene::update()
	{

	}

	const lib::vector2df MenuScene::getDefaultSizeView()
	{
		return{ 2000.0f, 2000.0f };
	}
}
