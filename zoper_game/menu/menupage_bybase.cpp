#include "menupage_bybase.hpp"
#include "menupagetype.hpp"
#include <lib/include/core/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>
#include "../common.hpp"
#include "../zoperprogramcontroller.hpp"
#include "../gameshareddata.hpp"

namespace zoper
{
	MenuPageByBase::MenuPageByBase(lib::scene::SceneNode *parent, str name) : MenuPage{ parent, std::move(name) } {}

    MenuPageByBase::~MenuPageByBase() {}

	void MenuPageByBase::onCreated()
	{
		BaseClass::onCreated();

        const str FirstOption(str("Start level ") + str(m_gameModePage == GameMode::Token?"token":"time") + str(" mode"));
		configure(MenuPageMode::Optioner, 
		{ std::move(FirstOption), "Play", "Back" }, { { "1","2", "3", "4", "5", "6", "7", "8", "9", "10" } });

		Selection.connect([this](const size_type index) {
			switch (index) {
			// Play
			case 1:
				zApp().gameSharedData->startLevel = SelectedOptionAtRow(0);
				zApp().gameSharedData->gameMode = m_gameModePage;
				zApp().gameSharedData->exitGame = false;
				log_debug_info("Selected level ", zApp().gameSharedData->startLevel,
					" GameMode: ", static_cast<u32>(zApp().gameSharedData->gameMode),
					" Exiting game: ", zApp().gameSharedData->exitGame);
				parentScene()->sceneManager().sceneController()->terminateScene();
				break;
			// Back
			case 2:
				Back();
				break;
			default:
				break;
			}
		});
	}
}
