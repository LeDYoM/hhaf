#include "keyredefinitionmenu.hpp"
#include "lib/menu/menumanager.hpp"
#include "lib/menu/choosecontrol.hpp"
#include "lib/menu/menudescriptors.hpp"
#include "lib/scn/draw/renderizable.hpp"
#include "lib/scn/resourcemanager.hpp"
#include "lib/scn/resource.hpp"

#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		KeyRedefinitionMenu::KeyRedefinitionMenu()
			: lib::menu::MenuStep{ "OptionsMenu" }, _gameConfig{ ":NextGame" }
		{
		}


		KeyRedefinitionMenu::~KeyRedefinitionMenu()
		{
		}

		void KeyRedefinitionMenu::onCreate()
		{
			_nextKeyText = createText("mainLogo");
			auto _nextKeyTextText = _nextKeyText->getAsText();
			auto rManager = menuManager()->resourceManager();

			_nextKeyTextText->setFont(*rManager->getResource("game_menu.mainFont")->getAsFont());
			_nextKeyTextText->setCharacterSize(90);
			_nextKeyTextText->setString(" ");
			_nextKeyTextText->setColor(sf::Color::Blue);
			_nextKeyText->setPosition(sf::Vector2f{ 0.0f, 0.0f }, lib::scn::draw::Alignment::Center);
		}
	}
}
