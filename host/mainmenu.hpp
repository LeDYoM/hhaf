#ifndef __MAINMENU_HPP__
#define __MAINMENU_HPP__

#include <lib/gui/choosecontrolgroup.hpp>
#include <lib/core/configuration.hpp>
#include <lib/scene/scenenode.hpp>

namespace zoper
{
	class GameConfig;
	namespace zmenu
	{
		class MainMenu : public lib::gui::ChooseControlGroup
		{
		public:
			constexpr static const char*ClassName = "MainMenu";
			MainMenu(lib::scene::SceneNode *parent, lib::str name);
			virtual ~MainMenu();

			virtual void create() override;
			virtual void configure() override;

		private:
			lib::sptr<GameConfig> m_gameConfig;
			lib::sptr<lib::gui::ChooseControl> m_chooseControl;
		};
	}
}

#endif