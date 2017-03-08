#include "keyredefinitionmenu.hpp"
#include <lib/gui/ChooseControlGroup.hpp>
#include <lib/gui/choosecontrol.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/draw/nodes/nodetext.hpp>
#include <lib/core/host.hpp>
#include "common.hpp"

using namespace lib;

namespace zoper
{
	namespace zmenu
	{
		using namespace lib;
		using namespace lib::draw;
		using namespace lib::draw::nodes;

		KeyRedefinitionMenu::KeyRedefinitionMenu(SceneNode *parent)
			: SceneNode{ parent, ClassName } {}

		KeyRedefinitionMenu::~KeyRedefinitionMenu() = default;

		void KeyRedefinitionMenu::create()
		{
			_nextKeyText = createRenderizable<NodeText>("pressKey");
			_nextKeyText->text = " ";
			_nextKeyText->font = host().resourceManager().getFont("game_menu.mainFont");
			_nextKeyText->characterSize = 90;
			_nextKeyText->color = colors::Blue;
			_nextKeyText->configure();
			//			_nextKeyText->setAlignment(Rectf32{ 0, 0, 1000.0f, 1000.0f }, NodeText::Alignment::Center);
			_indexKey = 0;
			setTextForKey();
		}

		void KeyRedefinitionMenu::setTextForKey()
		{
			if (_indexKey >= KeyMapping::TotalKeys)
			{
				_indexKey = 0;
				_keyMapping.apply();
				//				ChooseControlGroup()->changeStep("OptionsMenu");
			}
			else
			{
				_nextKeyText->text = "Press key for " + getKeyNameStr(_indexKey);
				//				_nextKeyText->setAlignment(Rectf32{ 0, 0, 1000.0f, 1000.0f }, NodeText::Alignment::Center);
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