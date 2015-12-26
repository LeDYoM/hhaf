#include "mainmenu.hpp"
#include "lib/menu/menumanager.hpp"
#include "lib/menu/choosecontrol.hpp"
#include "lib/menu/optiondescriptor.hpp"
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
			_logo->setPositionX(menuManager()->getCoordinatesToCenter(_logo->getAsSprite()->getLocalBounds()).x);
			_logo->setPositionY(100);

			_chooseControl = lib::sptr<lib::menu::ChooseControl>(new lib::menu::ChooseControl("mainmenu_chooseControl",
				rManager->getResource("game_menu.mainFont"),
				std::vector<lib::sptr<lib::menu::OptionDescriptor>>{
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Play", { 0.0f, 0.0f }, 45, sf::Color::Blue)),
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Options", { 0.0f, 0.0f }, 45, sf::Color::Blue)),
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Exit", { 0.0f, 0.0f }, 45, sf::Color::Blue)),
			}));
			addMenuControl(_chooseControl);
			_chooseControl->setPosition(100, 100);
		}
	}
}
