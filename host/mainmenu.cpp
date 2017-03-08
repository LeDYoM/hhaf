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
			: ChooseControlGroup{ parent, std::move(name) }, m_gameConfig{ ":NextGame" }
		{
						//			position.set({ 0,700 });
		}

		MainMenu::~MainMenu() = default;

		void MainMenu::create()
		{
			ChooseControlGroup::create();
		}

		void MainMenu::configure()
		{
			options = std::vector<std::vector<OptionModel>>
			{
				// Main menu
				{
					OptionModel("Play token mode"),
					OptionModel("Play time mode"),
					OptionModel("Options"),
					OptionModel("Exit")
				},
				// Start level menu
				{
					OptionModel("Start level: ", std::vector<str_const>{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" }),
					OptionModel("Back")
				}
			};

			onSelected = std::function<const OptionModelIndex(const std::vector<u32> &indices)>(
				[this](const std::vector<u32> &indices)
			{
				switch (indices[0])
				{
				case 0:
					__ASSERT(indices.size() > 1, "Error in the indices parameter");
					m_gameConfig.value(GameModeStr)->set<s32>(static_cast<s32>(indices[1]));
					return OptionModelIndex{ 1 };
					break;
				case 1:
				case 2:
					//						m_chooseControl->chooseControlGroup()->changeStep("OptionsMenu");
					return OptionModelIndex{};
					break;
				case 3:
				default:
					host().exitProgram();
					return OptionModelIndex{};
					break;
				}
			}
			);

			ChooseControlGroup::configure();
			currentControlIndex = 0;
		}
	}
}