#include "keyredefinitionmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/core/host.hpp>
#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		KeyRedefinitionMenu::KeyRedefinitionMenu(lib::draw::RenderGroup *parent)
			: lib::draw::RenderGroup{ "KeyRedefinitionMenu", parent }
		{
		}


		KeyRedefinitionMenu::~KeyRedefinitionMenu() = default;

		void KeyRedefinitionMenu::onAddedToScene()
		{
			_nextKeyText = createText("pressKey");

			_nextKeyText->setFont(*lib::host().resourceManager().getResource("game_menu.mainFont")->getAsFont());
			_nextKeyText->setCharacterSize(90);
			_nextKeyText->setString(" ");
			_nextKeyText->setColor(sf::Color::Blue);
			_nextKeyText->setPosition(sf::Vector2f{ 1000.0f, 1000.0f }, lib::draw::Alignment::Center);
			_indexKey = 0;
			setTextForKey();
		}

		void KeyRedefinitionMenu::setTextForKey()
		{
			if (_indexKey >= KeyMapping::TotalKeys)
			{
				_indexKey = 0;
				_keyMapping.apply();
//				menuManager()->changeStep("OptionsMenu");
			}
			else
			{
				_nextKeyText->setString("Press key for "+getKeyNameStr(_indexKey));
				_nextKeyText->setPosition(sf::Vector2f{ 1000.0,1000.0 }, lib::draw::Alignment::Center);
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
