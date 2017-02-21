#ifndef __MAINMENU_HPP__
#define __MAINMENU_HPP__

#include <lib/gui/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class MainMenu : public lib::gui::ChooseControl
		{
		public:
			constexpr static char* ClassName = "MainMenu";
			MainMenu(lib::gui::MenuManager *parent);
			virtual ~MainMenu();

			virtual void onAddedToScene() override;

		private:
			lib::Configuration m_gameConfig;
		};
	}
}

#endif
