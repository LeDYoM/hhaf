#include "startlevelmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/draw/renderizable.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
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
			: lib::menu::ChooseControl( ClassName, parent,
			[this](const u32 index)
			{
				switch (index)
				{
				case 0:
					_gameConfig.value(StartLevelStr)->set(getSelectedSubLabel(0));
					LOG_DEBUG("Starting at level:" << getSelectedSubLabel(0));
					setSelectedSubLabel(0, 0);
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
			setPosition({ MenuScene::MenuPosX, 700 });
		}
	}
}
