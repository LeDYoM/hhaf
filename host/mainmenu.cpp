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

		MainMenuController::MainMenuController(MenuManager *parent)
			: m_gameConfig{ ":NextGame" }
		{
			m_chooseControl = msptr<ChooseControl>(parent, ClassName,
			[this](const u32 index)
			{
				switch (index)
				{
				case 0:
					m_gameConfig.value(GameModeStr)->set<s32>(0);
					m_chooseControl->menuManager()->changeStep(StartLevelMenu::ClassName);
					break;
				case 1:
					m_gameConfig.value(GameModeStr)->set<s32>(1);
					m_chooseControl->menuManager()->changeStep("StartLevelMenu");
					break;
				case 2:
					m_chooseControl->menuManager()->changeStep("OptionsMenu");
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
			});

//			position.set({ 0,700 });
		}

		MainMenuController::~MainMenuController() = default;
	}
}
