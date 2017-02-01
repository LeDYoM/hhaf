#include "keyredefinitionmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/core/host.hpp>
#include "common.hpp"

using namespace lib;

namespace zoper
{
	namespace zmenu
	{
		using namespace lib;
		using namespace lib::draw;

		KeyRedefinitionMenu::KeyRedefinitionMenu(RenderGroup *parent)
			: RenderGroup{ ClassName, parent } {}

		KeyRedefinitionMenu::~KeyRedefinitionMenu() = default;

		void KeyRedefinitionMenu::onAddedToScene()
		{
			_nextKeyText = createRenderizable<NodeText>("pressKey"," ", lib::host().resourceManager().getFont("game_menu.mainFont"),90, colors::Blue);
			_nextKeyText->setPositionWithAlignment({ 1000.0f, 1000.0f }, NodeText::Alignment::Center);
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
				_nextKeyText->text = "Press key for "+getKeyNameStr(_indexKey);
				_nextKeyText->setPositionWithAlignment({ 1000.0,1000.0 }, NodeText::Alignment::Center);
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
