#include "startlevelmenu.hpp"
#include <lib/gui/menumanager.hpp>
#include <lib/gui/choosecontrol.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include "common.hpp"
#include "menuscene.hpp"

namespace zoper
{
	namespace zmenu
	{
		using namespace lib;
		using namespace lib::menu;

		StartLevelMenu::StartLevelMenu(MenuManager *parent)
			: ChooseControl( parent, ClassName,
			[this](const u32 index)
			{
				switch (index)
				{
				case 0:
					_gameConfig.value(StartLevelStr)->set(selectedSubLabel(0));
					logDebug("Starting at level:", selectedSubLabel(0));
					host().setScene("GameScene");

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
			position = { MenuScene::MenuPosX, 700 };
		}
	}
}
