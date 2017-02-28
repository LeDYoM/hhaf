#ifndef __MAINMENU_HPP__
#define __MAINMENU_HPP__

#include <lib/gui/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class MainMenuController
		{
		public:
			constexpr static char* ClassName = "MainMenu";
			MainMenuController(lib::gui::ChooseControlGroup *parent);
			virtual ~MainMenuController();

		private:
			lib::Configuration m_gameConfig;
			lib::sptr<lib::gui::ChooseControl> m_chooseControl;
		};
	}
}

#endif
