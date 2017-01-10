#ifndef __MAINMENU_HPP__
#define __MAINMENU_HPP__

#include <lib/menu/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class MainMenu : public lib::menu::ChooseControl
		{
		public:
			constexpr static char* ClassName = "MainMenu";
			MainMenu(lib::menu::MenuManager *parent);
			virtual ~MainMenu();

			virtual void onAddedToScene() override;

		private:
			lib::Configuration m_gameConfig;
		};
	}
}

#endif
