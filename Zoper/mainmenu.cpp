#include "mainmenu.hpp"
#include "lib/menu/menumanager.hpp"
#include "lib/menu/choosecontrol.hpp"
#include "lib/menu/menudescriptors.hpp"
#include "lib/scn/draw/renderizable.hpp"
#include "lib/scn/resourcemanager.hpp"
#include "lib/scn/resource.hpp"

namespace zoper
{
	namespace zmenu
	{
		MainMenu::MainMenu()
			: lib::menu::MenuStep{ "MainMenu" }
		{
		}


		MainMenu::~MainMenu()
		{
		}

		void MainMenu::onCreate()
		{
			_logo = createSprite("mainLogo");
			auto _logoSprite = _logo->getAsSprite();
			auto rManager = menuManager()->resourceManager();
			_logoSprite->setTexture(*(rManager->getResource("game_menu.logo")->getAsTexture()));
			_logoSprite->setScale(2.0f, 2.0f);
			_logo->setPositionX(menuManager()->getCoordinatesToCenter(_logo->getAsSprite()->getGlobalBounds()).x);
			_logo->setPositionY(100);

			_chooseControl = lib::sptr<lib::menu::ChooseControl>(new lib::menu::ChooseControl("mainmenu_chooseControl",
				rManager->getResource("game_menu.mainFont"),
				90, 1,
				lib::sptr<lib::menu::CursorDescriptor>(new lib::menu::CursorDescriptor(3, lib::vector2df{ 90.0f, 90.0f },sf::Color::Red)),
				std::vector<lib::sptr<lib::menu::OptionDescriptor>>{
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Play", sf::Color::Blue)),
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Options", sf::Color::Blue)),
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Exit", sf::Color::Blue)),
			}));
			addMenuControl(_chooseControl);
			_chooseControl->setPosition(700, 700);
		}
	}
}
