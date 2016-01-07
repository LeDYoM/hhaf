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
			: lib::menu::MenuStep{ "KeyRedefinitionMenu" }, _gameConfig{ ":NextGame" }
		{
		}


		KeyRedefinitionMenu::~KeyRedefinitionMenu()
		{
		}

		void KeyRedefinitionMenu::onCreate()
		{
			_nextKeyText = createText("pressKey");
			auto _nextKeyTextText = _nextKeyText->getAsText();
			auto rManager = menuManager()->resourceManager();

			_nextKeyTextText->setFont(*rManager->getResource("game_menu.mainFont")->getAsFont());
			_nextKeyTextText->setCharacterSize(90);
			_nextKeyTextText->setString(" ");
			_nextKeyTextText->setColor(sf::Color::Blue);
			_nextKeyText->setPosition(sf::Vector2f{ 0.0f, 0.0f }, lib::scn::draw::Alignment::Center);
			_indexKey = 0;
		}

		void KeyRedefinitionMenu::onKeyPressed(sf::Event::KeyEvent kEvent)
		{
			lib::menu::MenuStep::onKeyPressed(kEvent);
			if (_keyMapping.setKey(_indexKey, kEvent.code))
			{
				++_indexKey;
				setTextForKey();
			}
		}

		void KeyRedefinitionMenu::onKeyReleased(sf::Event::KeyEvent kEvent)
		{
			lib::menu::MenuStep::onKeyReleased(kEvent);
		}

		void KeyRedefinitionMenu::setTextForKey()
		{
			if (_indexKey >= KeyMapping::TotalKeys)
			{
				_indexKey = 0;
				menuManager()->changeStep("OptionsMenu");
			}
			else
			{
				_nextKeyText->getAsText()->setString(getKeyNameStr(_indexKey));
			}
		}

		const std::string KeyRedefinitionMenu::getKeyNameStr(const lib::u32 index) const
		{
			switch (index)
			{
			case 0:
				return "Left";
				break;
			case 1:
				return "Right";
				break;
			case 2:
				return "Up";
				break;
			case 3:
				return "Down";
				break;
			case 4:
				return "Launch";
				break;
			default:
			case 5:
				return "Pause";
				break;
			}
		}
	}
}
