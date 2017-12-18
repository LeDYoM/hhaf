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
		m_gameData = app<ZoperProgramController>().gameData;
	}

	MainMenu::~MainMenu() = default;

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

		menuPageMain->Forward.connect([this,statesController](const MenuPageType selectedIndex) {
			switch (selectedIndex)
			{
			case MenuPageType::SelectLevelToken:
				statesController->push_state(MenuPageType::SelectLevelToken);
				break;
			case MenuPageType::SelectLevelSpeed:
                m_gameData->startGameData.gameMode = GameMode::Time;
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

		menuPageMain->Back.connect([statesController]() {
			statesController->pop_state();
		});
		menuPageByToken->Back.connect([statesController]() {
			statesController->pop_state();
		});
		menuPageByTime->Back.connect([statesController]() {
			statesController->pop_state();
		});
		menuPageOptions->Back.connect([statesController]() {
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

		statesController->AfterFinish.connect([this]() {
			MenuFinished();
		});
		statesController->start(MenuPageType::Main);
	}

	void MainMenu::showPage(const MenuPageType &newPage)
	{
		m_menuSteps[static_cast<int>(newPage)]->visible = true;
	}

	void MainMenu::hidePage(const MenuPageType &page)
	{
		m_menuSteps[static_cast<int>(page)]->visible = false;
	}
}
