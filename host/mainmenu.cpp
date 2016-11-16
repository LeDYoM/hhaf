#include "mainmenu.hpp"
#include "startlevelmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/menu/menudescriptors.hpp>
#include <lib/draw/rendergroup.hpp>
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

		MainMenu::MainMenu(MenuManager *parent)
			: lib::menu::ChooseControl( ClassName, parent,
			[this](const u32 index)
			{
				switch (index)
				{
				case 0:
//					_gameConfig.addConfigInt(GameModeStr, 0, true);
					menuManager()->changeStep(StartLevelMenu::ClassName);
					break;
				case 1:
//					_gameConfig.addConfigInt(GameModeStr, 1, true);
					menuManager()->changeStep("StartLevelMenu");
					break;
				case 2:
					menuManager()->changeStep("OptionsMenu");
					break;
				case 3:
				default:
					host().exitProgram();
					break;
				}
			},
			std::vector<sptr<OptionDescriptor>>{
			msptr<OptionDescriptor>("Play token mode"),
				msptr<OptionDescriptor>("Play time mode"),
				msptr<OptionDescriptor>("Options"),
				msptr<OptionDescriptor>("Exit")
			}),
			_gameConfig{ ":NextGame" }
		{
		}


		MainMenu::~MainMenu() = default;

		void MainMenu::onAddedToScene()
		{
			setPosition(menuManager()->getCenterCoordinates().x, 700);
		}
	}
}
