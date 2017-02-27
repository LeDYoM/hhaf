#include "mainmenu.hpp"
#include "startlevelmenu.hpp"
#include <lib/gui/menumanager.hpp>
#include <lib/gui/choosecontrol.hpp>
#include <lib/draw/scenenode.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		using namespace lib;
		using namespace lib::gui;

		MainMenu::MainMenu(MenuManager *parent) 
			: ChooseControl( parent, ClassName, 
			[this](const u32 index)
			{
				switch (index)
				{
				case 0:
					m_gameConfig.value(GameModeStr)->set<s32>(0);
					menuManager()->changeStep(StartLevelMenu::ClassName);
					break;
				case 1:
					m_gameConfig.value(GameModeStr)->set<s32>(1);
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
			m_gameConfig{ ":NextGame" }
		{
//			position.set({ 0,700 });
		}

		MainMenu::~MainMenu() = default;

		void MainMenu::onAddedToScene()
		{
		}
	}
}
