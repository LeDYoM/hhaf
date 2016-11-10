#include "startlevelmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/menu/menudescriptors.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
#include <lib/core/host.hpp>
#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		using namespace lib;
		using namespace lib::menu;

		StartLevelMenu::StartLevelMenu(MenuManager *parent)
			: lib::menu::ChooseControl( "StartLevelMenu", parent,
			[this](lib::u32 index, lib::menu::ChooseControl &self)
			{
				switch (index)
				{
				case 0:
					_gameConfig.addConfigInt(StartLevelStr, self.getSelectedSubLabel(0), true);
					LOG_DEBUG("Starting at level:" << self.getSelectedSubLabel(0));
					self.setSelectedSubLabel(0, 0);
					lib::host().setScene("GameScene");

					break;
				default:
				case 1:
					menuManager()->changeStep("MainMenu");
					break;
				}
			},
			std::vector<sptr<OptionDescriptor>>{
			msptr<OptionDescriptor>("Start level: ",
				true, 0, std::vector<std::string>{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" }),
				msptr<OptionDescriptor>("Back", true)
			}), 
			Configuration("config.cfg"), _gameConfig{ ":NextGame" }
		{
		}

		StartLevelMenu::~StartLevelMenu() = default;

		void StartLevelMenu::onAddedToScene()
		{
			setPosition(300, 700);
		}
	}
}
