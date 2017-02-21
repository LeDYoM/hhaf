#ifndef __STARTLEVELMENU_HPP__
#define __STARTLEVELMENU_HPP__

#include <lib/gui/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class StartLevelMenu : public lib::menu::ChooseControl, public lib::Configuration
		{
		public:
			constexpr static char* ClassName = "StartLevelMenu";
			StartLevelMenu(lib::menu::MenuManager *parent);
			virtual ~StartLevelMenu();
			virtual void onAddedToScene() override;

		private:
			lib::Configuration _gameConfig;
		};
	}
}

#endif
