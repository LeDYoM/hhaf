#include "mainmenu.hpp"
#include <lib/gui/ChooseControlGroup.hpp>
#include <lib/gui/choosecontrol.hpp>
#include <lib/draw/scenenode.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include <lib/include/logcl.hpp>
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
					OptionModel("Play token mode",{}, OptionModelIndex{ 1 }),
					OptionModel("Play time mode", {}, OptionModelIndex{ 1 }),
					OptionModel("Options", {}, OptionModelIndex{ 2 }),
					OptionModel("Exit")
				},
				// Start level menu
				{
					OptionModel("Start level: ", {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" }),
					OptionModel("Back",{},{ 0 })
				},
				// Options menu
				{
					OptionModel("Antialiasing", {"Worst", "Bad", "Normal", "Good", "Best"}),
					OptionModel("Resolution", {"Worst", "Bad", "Normal", "Good", "Best"}),
					OptionModel("Fullscreen", {"No", "Yes"}),
					OptionModel("VSync", {"No", "Yes"}),
					OptionModel("Redefine keyboard"),
					OptionModel("Cancel", {}, OptionModelIndex{ 0 }),
					OptionModel("Accept", {}, OptionModelIndex{ 0 })
				}
			};

			onSelected = std::function<const OptionModelIndex(const std::vector<u32> &indices)>(
				[this](const std::vector<u32> &indices)
			{
				switch (indices[0])
				{
				case 0:
					// Main menu page
					CLIENT_ASSERT(indices.size() > 1, "Error in the indices parameter");
					switch (indices[1])
					{
					case 0:
					case 1:
						// Go to start level (token or time)
						m_gameConfig.value(GameModeStr)->set<s32>(static_cast<s32>(indices[1]));
						break;

					case 3:
						// Exit
						// TO DO
						host().exitProgram();
						break;
					default:
						break;
					}
					break;
				case 1:
					// Start level (token or time)
					CLIENT_ASSERT(indices.size() > 1, "Error in the indices parameter");
					switch (indices[1])
					{
					case 0:
						// Start level option
						CLIENT_ASSERT(indices.size() > 2, "Error in indices parameter");
						m_gameConfig.value(StartLevelStr)->set(indices[2]);
						logClDebug("Starting at level:", indices[2]);
						lib::host().setScene("GameScene");
						break;
					default:
						// Back option
						logClDebug("Going back from Start Level menu to main menu");
						break;
					}
					break;

				case 2:
					// Options menu
					CLIENT_ASSERT(indices.size() > 1, "Error in the indices parameter");
					switch (indices[1])
					{
						// Antialiasing, Resolution, Fullscreen, VSync
					case 4:
						// Redefine keyboard
						// TO DO
						break;
					case 5:
						// Cancel
						// TO DO
						// Avoid modifying options
					case 6:
						// Accept
					default:
						break;
					}
					break;
				case 3:
				default:
					break;
				}
				return OptionModelIndex{};
			});

			ChooseControlGroup::configure();
			currentControlIndex = 0;
		}
	}
}