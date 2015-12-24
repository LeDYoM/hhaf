#include "mainmenu.hpp"
#include "lib/menu/menumanager.hpp"
#include "lib/menu/choosecontrol.hpp"
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
			_logoSprite->setTexture(*(menuManager()->resourceManager()->getResource("game_menu.logo")->getAsTexture()));
			_logo->setPositionX(menuManager()->getCoordinatesToCenter(_logo->getAsSprite()->getLocalBounds()).x);

			
		}

	}
}
