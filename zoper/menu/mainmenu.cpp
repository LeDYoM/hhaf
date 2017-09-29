#include "mainmenu.hpp"
#include "../gamedata.hpp"
#include "../zoperprogramcontroller.hpp"


#include <lib/scene/nodes/choosecontrol.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/core/host.hpp>
#include <mtypes/include/log.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/components/statescontroller.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::scene::nodes;

	enum class MenuPages
	{
		Main,
		SelectLevelToken,
		SelectLevelSpeed,
		Options
	};

	MainMenu::MainMenu(SceneNode *parent, str name)
		: SceneNode{ parent, std::move(name) } 
	{
		m_gameData = host().app<ZoperProgramController>().gameData;
	}

	MainMenu::~MainMenu() = default;

	template<typename T, void (T::*sm)(const MenuPage&p1,const MenuPage&p2)>
	function<void(const MenuPage&, const MenuPage&)> ml(T&obj) {
		return [&obj](const MenuPage&p1, const MenuPage&p2) {(obj.(*sm))(p1,p2); };
	}

	void MainMenu::create()
	{
		using namespace nodes;
		SceneNode::create();
		auto statesController = emplaceComponentOfType<StatesController<MenuPages>>(MenuPages::Main);
//		statesController->stateChanged.connect(ml<MainMenu,&MainMenu::mainMenuPageChanged>(*this));
//		statesController->stateChanged.connect([this](const auto a1, const auto a2) { mainMenuPageChanged(a1, a2); });
		statesController->stateChanged.connect(this, &MainMenu::mainMenuPageChanged);

		EventHandlerImpl<MainMenu, const MenuPage&, const MenuPage&> a(this, &MainMenu::mainMenuPageChanged);
		function<void(const MenuPage&, const MenuPage&)> b(this, &MainMenu::mainMenuPageChanged);
//			statesController->stateChanged.connect
		options = vector<vector<OptionModel>>
		{
			// Main menu
			{
				OptionModel("Play token mode",{}, OptionModelIndex{ 1 }),
				OptionModel("Play time mode",{}, OptionModelIndex{ 1 }),
				OptionModel("Options",{}, OptionModelIndex{ 2 }),
				OptionModel("Exit")
			},
			// Start level menu
			{
				OptionModel("Start level: ",{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" }),
				OptionModel("Back",{},{ 0 })
			},
			// Options menu
			{
				OptionModel("Antialiasing",{ "Worst", "Bad", "Normal", "Good", "Best" }),
				OptionModel("Resolution",{ "Worst", "Bad", "Normal", "Good", "Best" }),
				OptionModel("Fullscreen",{ "No", "Yes" }),
				OptionModel("VSync",{ "No", "Yes" }),
				OptionModel("Redefine keyboard"),
				OptionModel("Cancel",{}, OptionModelIndex{ 0 }),
				OptionModel("Accept",{}, OptionModelIndex{ 0 })
			}
		};

		onSelected = lib::function<const OptionModelIndex(const vector<u32> &indices)>(
			[this](const vector<u32> &indices)
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
					m_gameData->gameMode = static_cast<s32>(indices[1]);
					break;
				case 3:
					// Exit
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
					m_gameData->startLevel = indices[2];
					lib::log_debug_info("Starting at level:", indices[2]);
					sceneManager().terminateScene();
					break;
				default:
					// Back option
					lib::log_debug_info("Going back from Start Level menu to main menu");
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

		position = { 0, 700 };
		box.set(scenePerspective().setRadiusFromCenter({ 800, 1000 }));

		ChooseControlGroup::configure();
		currentControlIndex = 0;

	}

	/*
	void MainMenu::create()
	{
	ChooseControlGroup::create();
	options = vector<vector<OptionModel>>
	{
	// Main menu
	{
	OptionModel("Play token mode",{}, OptionModelIndex{ 1 }),
	OptionModel("Play time mode",{}, OptionModelIndex{ 1 }),
	OptionModel("Options",{}, OptionModelIndex{ 2 }),
	OptionModel("Exit")
	},
	// Start level menu
	{
	OptionModel("Start level: ",{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" }),
	OptionModel("Back",{},{ 0 })
	},
	// Options menu
	{
	OptionModel("Antialiasing",{ "Worst", "Bad", "Normal", "Good", "Best" }),
	OptionModel("Resolution",{ "Worst", "Bad", "Normal", "Good", "Best" }),
	OptionModel("Fullscreen",{ "No", "Yes" }),
	OptionModel("VSync",{ "No", "Yes" }),
	OptionModel("Redefine keyboard"),
	OptionModel("Cancel",{}, OptionModelIndex{ 0 }),
	OptionModel("Accept",{}, OptionModelIndex{ 0 })
	}
	};

	onSelected = lib::function<const OptionModelIndex(const vector<u32> &indices)>(
	[this](const vector<u32> &indices)
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
	m_gameData->gameMode = static_cast<s32>(indices[1]);
	break;
	case 3:
	// Exit
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
	m_gameData->startLevel = indices[2];
	lib::log_debug_info("Starting at level:", indices[2]);
	sceneManager().terminateScene();
	break;
	default:
	// Back option
	lib::log_debug_info("Going back from Start Level menu to main menu");
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

	position = { 0, 700 };
	box.set(scenePerspective().setRadiusFromCenter({ 800, 1000 }));

	ChooseControlGroup::configure();
	currentControlIndex = 0;

	}
	*/

	void MainMenu::configure()
	{
	}

	void MainMenu::mainMenuPageChanged(const MenuPage &, const MenuPage &)
	{
	}
}
