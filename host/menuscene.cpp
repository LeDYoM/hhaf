#include "menuscene.hpp"
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
#include <lib/core/host.hpp>
#include <lib/core/eventmanager.hpp>
#include <lib/include/events/inputevent.hpp>

#include "mainmenu.hpp"
#include "optionsmenu.hpp"
#include "keyredefinitionmenu.hpp"
#include "startlevelmenu.hpp"

namespace zoper
{
	using namespace lib;

	MenuScene::MenuScene()
		: lib::menu::MenuManager("MenuScene")
	{
	}


	MenuScene::~MenuScene()
	{
	}

	void MenuScene::onInit()
	{
		_background = createSpriteShape("background");

		addMenuStep(msptr<zmenu::MainMenu>(this));
		addMenuStep(msptr<zmenu::OptionsMenu>(this));
//		addMenuStep(msptr<zmenu::KeyRedefinitionMenu>(this));
		addMenuStep(msptr<zmenu::StartLevelMenu>(this));

		_logo = createSpriteShape("mainLogo");
		_logo->setTexture(lib::host().resourceManager().getResource("game_menu.logo")->getAsTexture(), true, false);
		_logo->setSize(sf::Vector2f(800, 400));
		_logo->setPositionX(getCenterCoordinates().x, lib::scn::draw::Alignment::Center);
		_logo->setPositionY(100);

		_background->setTexture(lib::host().resourceManager().getResource("game_menu.background")->getAsTexture(), true, false);
		_background->setSize(2000.0f);
	}

	void MenuScene::onDeinit()
	{

	}

	void MenuScene::onEnterScene()
	{
		start("MainMenu");
		eventConnector.addSubscription(events::KeyPressedEvent::subscribe([this](const events::Event&) {
			LOG_DEBUG("Key pressed on menu : " << name());
		}));
	}

	void MenuScene::onExitScene()
	{
		eventConnector.unsubscribeAll();
	}

	void MenuScene::update()
	{

	}

	const lib::vector2df MenuScene::getDefaultSizeView()
	{
		return{ 2000.0f, 2000.0f };
	}
}
