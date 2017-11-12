#include "mainmenu.hpp"
#include "../gamedata.hpp"
#include "../zoperprogramcontroller.hpp"
#include "menupage.hpp"
#include "menupage_main.hpp"
#include "menupage_bytoken.hpp"
#include "menupage_bytime.hpp"
#include "menupage_options.hpp"
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

	MainMenu::MainMenu(SceneNode *parent, str name)
		: SceneNode{ parent, std::move(name) } 
	{
		m_gameData = host().app<ZoperProgramController>().gameData;
	}

	MainMenu::~MainMenu() = default;

	void MainMenu::showPage(const MenuPageType &newPage)
	{
		m_menuSteps[static_cast<int>(newPage)]->visible = true;
	}

	void MainMenu::hidePage(const MenuPageType &page)
	{
		m_menuSteps[static_cast<int>(page)]->visible = false;
	}

	void MainMenu::create()
	{
		using namespace nodes;
		SceneNode::create();

		auto statesController = ensureComponentOfType<StatesController<MenuPageType>>();
		statesController->UseDeferred();

		// Create and register menu pages
		auto menuPageMain(createSceneNode<MenuPageMain>("menuPageMain"));
		m_menuSteps.push_back(menuPageMain);
		auto menuPageByToken(createSceneNode<MenuPageByToken>("menuPageByToken"));
		m_menuSteps.push_back(menuPageByToken);
		auto menuPageByTime(createSceneNode<MenuPageByTime>("menuPageByTime"));
		m_menuSteps.push_back(menuPageByTime);
		auto menuPageOptions(createSceneNode<MenuPageOptions>("menuPageOptions"));
		m_menuSteps.push_back(menuPageOptions);


		menuPageMain->Forward.connect([statesController](const MenuPageType selectedIndex) {
			switch (selectedIndex)
			{
			case MenuPageType::SelectLevelToken:
				statesController->push_state(MenuPageType::SelectLevelToken);
				break;
			case MenuPageType::SelectLevelSpeed:
				statesController->push_state(MenuPageType::SelectLevelSpeed);
				break;
			case MenuPageType::Options:
				statesController->push_state(MenuPageType::Options);
				break;
			default:
				statesController->pop_state();
				break;
			}
		});

		menuPageByToken->Back.connect([statesController]() {
			statesController->pop_state();
		});
		menuPageByTime->Back.connect([statesController]() {
			statesController->pop_state();
		});

		statesController->StatePushed.connect([this](const MenuPageType menuPage) {
			showPage(menuPage);
		});
		statesController->StateResumed.connect([this](const MenuPageType menuPage) {
			showPage(menuPage);
		});

		statesController->StatePaused.connect([this](const MenuPageType menuPage) {
			hidePage(menuPage);
		});
		statesController->StatePopped.connect([this](const MenuPageType menuPage) {
			hidePage(menuPage);
		});

		statesController->BeforeStart.connect([this](const MenuPageType) {
			for (auto&& menuStep : m_menuSteps) {
				menuStep->visible = false;
			}
		});
		statesController->start(MenuPageType::Main);
//		statesController->stateChanged.connect(ml<MainMenu,&MainMenu::mainMenuPageChanged>(*this));
//		statesController->stateChanged.connect([this](const auto a1, const auto a2) { mainMenuPageChanged(a1, a2); });
//		statesController->stateChanged.connect(this, &MainMenu::mainMenuPageChanged);

//		ireceiver t;
//		t.connect(statesController->stateChanged, [](auto, auto) {});


//			statesController->stateChanged.connect
/*
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
		*/
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
}
