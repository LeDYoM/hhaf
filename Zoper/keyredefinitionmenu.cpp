#include "keyredefinitionmenu.hpp"
#include "lib/menu/menumanager.hpp"
#include "lib/menu/choosecontrol.hpp"
#include "lib/menu/menudescriptors.hpp"
#include "lib/scn/draw/renderizable.hpp"
#include "lib/scn/resourcemanager.hpp"
#include "lib/scn/resource.hpp"
#include "lib/scn/draw/nodetext.hpp"

#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		KeyRedefinitionMenu::KeyRedefinitionMenu()
			: lib::menu::MenuStep{ "KeyRedefinitionMenu" }
		{
		}


		KeyRedefinitionMenu::~KeyRedefinitionMenu()
		{
		}

		void KeyRedefinitionMenu::onCreate()
		{
			_nextKeyText = createText("pressKey");
			auto rManager = menuManager()->resourceManager();

			_nextKeyText->setFont(*rManager->getResource("game_menu.mainFont")->getAsFont());
			_nextKeyText->setCharacterSize(90);
			_nextKeyText->setString(" ");
			_nextKeyText->setColor(sf::Color::Blue);
			_nextKeyText->setPosition(sf::Vector2f{ 1000.0f, 1000.0f }, lib::scn::draw::Alignment::Center);
			_indexKey = 0;
			setTextForKey();
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
				_keyMapping.apply();
				menuManager()->changeStep("OptionsMenu");
			}
			else
			{
				_nextKeyText->setString("Press key for "+getKeyNameStr(_indexKey));
				_nextKeyText->setPosition(sf::Vector2f{ 1000.0,1000.0 }, lib::scn::draw::Alignment::Center);
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
