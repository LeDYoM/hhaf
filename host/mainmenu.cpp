#include "mainmenu.hpp"
#include "startlevelmenu.hpp"
#include <lib/gui/ChooseControlGroup.hpp>
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

		MainMenu::MainMenu(lib::draw::SceneNode *parent, str_const &&name)
			: ChooseControlGroup{ parent, std::move(name) }, m_gameConfig { ":NextGame" }
		{
//			m_chooseControl = createSceneNode<ChooseControl>(ClassName);
/*			[this](const u32 index)
			{
				switch (index)
				{
				case 0:
					m_gameConfig.value(GameModeStr)->set<s32>(0);
					m_chooseControl->chooseControlGroup()->changeStep(StartLevelMenu::ClassName);
					break;
				case 1:
					m_gameConfig.value(GameModeStr)->set<s32>(1);
					m_chooseControl->chooseControlGroup()->changeStep("StartLevelMenu");
					break;
				case 2:
					m_chooseControl->chooseControlGroup()->changeStep("OptionsMenu");
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
			*/
//			position.set({ 0,700 });
		}

		MainMenu::~MainMenu() = default;

		void MainMenu::create()
		{
			ChooseControlGroup::create();
		}

		void MainMenu::configure()
		{
			options = std::vector<std::vector<OptionModel>>{
				{OptionModel("Play token mode"),
				OptionModel("Play time mode"),
				OptionModel("Options"),
				OptionModel("Exit")}
			};

			onSelected = std::vector<std::function<void(const u32)>>{
				[this](const u32 index)
				{
					switch (index)
					{
					case 0:
						m_gameConfig.value(GameModeStr)->set<s32>(0);
//						m_chooseControl->chooseControlGroup()->changeStep(StartLevelMenu::ClassName);
					break;
					case 1:
						m_gameConfig.value(GameModeStr)->set<s32>(1);
//						m_chooseControl->chooseControlGroup()->changeStep("StartLevelMenu");
					break;
					case 2:
//						m_chooseControl->chooseControlGroup()->changeStep("OptionsMenu");
					break;
					case 3:
					default:
						host().exitProgram();
					break;
					}
				}
			};

			ChooseControlGroup::configure();
		}
	}
}
