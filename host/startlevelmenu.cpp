#include "startlevelmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/menu/menudescriptors.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>

#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		StartLevelMenu::StartLevelMenu()
			: lib::menu::MenuStep{ "StartLevelMenu" }, lib::Configuration("config.cfg"), _gameConfig{ ":NextGame" }
		{
		}


		StartLevelMenu::~StartLevelMenu()
		{
		}

		void StartLevelMenu::onCreate()
		{
			auto callBack = [this](lib::u32 index, lib::menu::ChooseControl &self)
			{
				switch (index)
				{
				case 0:
					_gameConfig.addConfigInt(StartLevelStr, self.getSelectedSubLabel(0), true);
					LOG_DEBUG("Starting t level:" << self.getSelectedSubLabel(0));
					self.setSelectedSubLabel(0, 0);
					menuManager()->setNextScene("GameScene");

					break;
				default:
				case 1:
					menuManager()->changeStep("MainMenu");
					break;
				}
			};
			_chooseControl = lib::sptr<lib::menu::ChooseControl>(new lib::menu::ChooseControl("optionsmenu_chooseControl",
				menuManager()->resourceManager()->getResource("game_menu.mainFont"), sf::Color::Blue, sf::Color::Red,
				lib::scn::draw::Alignment::Left,
				70, 1,
				callBack,
				lib::sptr<lib::menu::CursorDescriptor>(new lib::menu::CursorDescriptor(3, lib::vector2df{ 70.0f, 70.0f }, sf::Color::Red)),
				std::vector<lib::sptr<lib::menu::OptionDescriptor>>{
				lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Start level: ", 
					true, 0, std::vector<std::string>{"1", "2", "3", "4","5", "6","7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" })),
					lib::sptr<lib::menu::OptionDescriptor>(new lib::menu::OptionDescriptor("Back", true))
			}));
			addMenuControl(_chooseControl);
			_chooseControl->setPosition(100, 700);
		}
	}
}
