#include "mainmenu.hpp"

namespace zoper
{
	namespace menu
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
			_logoSprite->setTexture(*(resourceManager()->getResource("game_menu.logo")->getAsTexture()));
			_logo->setPositionX(getCoordinatesToCenter(_logo->getAsSprite()->getLocalBounds()).x);
		}

	}
}
