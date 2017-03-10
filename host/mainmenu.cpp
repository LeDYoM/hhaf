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
					OptionModel("Start level: ", string_vector{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" }),
					OptionModel("Back")
				},
				// Options menu
				{
					OptionModel("Antialiasing", string_vector{"Worst", "Bad", "Normal", "Good", "Best"}),
					OptionModel("Resolution", string_vector{"Worst", "Bad", "Normal", "Good", "Best"}),
					OptionModel("Fullscreen", string_vector{"No", "Yes"}),
					OptionModel("VSync", string_vector{"No", "Yes"}),
					OptionModel("Redefine keyboard"),
					OptionModel("Cancel"),
					OptionModel("Accept")
				}
			};

			onSelected = std::function<const OptionModelIndex(const std::vector<u32> &indices)>(
				[this](const std::vector<u32> &indices)
			{
				switch (indices[0])
				{
				case 0:
					// Main menu page
					__ASSERT(indices.size() > 1, "Error in the indices parameter");
					switch (indices[1])
					{
					case 0:
					case 1:
						// Go to start level (token or time)
						m_gameConfig.value(GameModeStr)->set<s32>(static_cast<s32>(indices[1]));
						return OptionModelIndex{ 1 };
						break;

					case 2:
						// Go to Options menu
						return OptionModelIndex{ 2 };
						break;

					case 3:
						// Exit
						// TO DO
						break;
					default:
						__ASSERT(false, "Unexpected switch value ");
					}
					break;
				case 1:
					// Start level (token or time)
					__ASSERT(indices.size() > 1, "Error in the indices parameter");
					switch (indices[1])
					{
					case 0:
						// Start level option
						__ASSERT(indices.size() > 2, "Error in indices parameter");
						m_gameConfig.value(StartLevelStr)->set(indices[2]);
						logDebug("Starting at level:", indices[2]);
						break;
					default:
						// Back option
						logDebug("Going back from Start Level menu to main menu");
						return OptionModelIndex{ 0 };
						break;
					}
					break;

				case 2:
					// Options menu
					__ASSERT(indices.size() > 1, "Error in the indices parameter");
					switch (indices[1])
					{
						// Antialiasing, Resolution, Fullscreen, VSync
					case 0:
					case 1:
					case 2:
					case 3:
						break;
					case 4:
						// Redefine keyboard
						// TO DO
						break;
					case 5:
						// Cancel
						// TO DO
						// Avoid modifying options
						return OptionModelIndex{ 0 };
					case 6:
						// Accept
						return OptionModelIndex{ 0 };
					default:
						__ASSERT(false, "Invalid option");
					}
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