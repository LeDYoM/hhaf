#include "optionsmenu.hpp"
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
		OptionsMenu::OptionsMenu()
			: lib::menu::MenuStep{ "OptionsMenu" }, _gameConfig{ ":NextGame" }
		{
		}


		OptionsMenu::~OptionsMenu()
		{
		}

		void OptionsMenu::onCreate()
		{
			auto rManager = menuManager()->resourceManager();
			/*
			auto initCallback = [this](lib::u32 index, lib::sptr<lib::scn::draw::Renderizable> node, 
				const lib::u32 subNodeIndexSelected, lib::sptr<lib::scn::draw::Renderizable> subNode)
			{
				auto subNode_ = subNode->getAsText();
				switch (index)
				{
				case 0:
					subNode_->setString("A");
					subNode->setPositionX(1800, lib::scn::draw::Alignment::Right);
					break;
				case 1:
					subNode_->setString("1024x768");
					if (subNodeIndexSelected > sf::VideoMode::getFullscreenModes().size())
					subNode->setPositionX(1800, lib::scn::draw::Alignment::Right);
					break;
				case 2:
					subNode_->setString("No");
					subNode->setPositionX(1800, lib::scn::draw::Alignment::Right);
					break;
				case 3:
					subNode_->setString("No");
					subNode->setPositionX(1800, lib::scn::draw::Alignment::Right);
					break;
				case 4:
					break;
				case 5:
				default:
					menuManager()->changeStep("MainMenu");
					break;
				}
			};
			*/
			auto callBack = [this](lib::u32 index/*, lib::sptr<lib::scn::draw::Renderizable> node, 
				const lib::u32 subNodeIndexSelected, lib::sptr<lib::scn::draw::Renderizable> subNode*/)
			{
				switch (index)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
				default:
					menuManager()->changeStep("MainMenu");
					break;
				}
			};
			_chooseControl = lib::sptr<lib::menu::ChooseControl>(new lib::menu::ChooseControl("optionsmenu_chooseControl",
				rManager->getResource("game_menu.mainFont"),
				lib::scn::draw::Alignment::Left,
				70, 1,
				callBack,
//				initCallback,
				lib::sptr<lib::menu::CursorDescriptor>(new lib::menu::CursorDescriptor(3, lib::vector2df{ 70.0f, 70.0f }, sf::Color::Red)),
				std::vector<lib::sptr<lib::menu::OptionDescriptor>>{
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Graphics quality", sf::Color::Blue
					,true,0,std::vector<std::string>{"Worst","Bad","Normal","Good","Best"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Resolution", sf::Color::Blue
						, true, 0, std::vector<std::string>{"Worst", "Bad", "Normal", "Good", "Best"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Fullscreen", sf::Color::Blue
					, true, 0, std::vector<std::string>{"No", "Yes"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("VSync", sf::Color::Blue
						, true, 0, std::vector<std::string>{"No", "Yes"})),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Redefine keyboard", sf::Color::Blue)),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Back", sf::Color::Blue,true)),
			}));
			addMenuControl(_chooseControl);
			_chooseControl->setPosition(100, 700);
		}
	}
}
