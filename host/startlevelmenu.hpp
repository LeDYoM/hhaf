#ifndef __STARTLEVELMENU_HPP__
#define __STARTLEVELMENU_HPP__

#include <lib/gui/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class StartLevelMenu : public lib::gui::ChooseControl, public lib::Configuration
		{
		public:
			constexpr static char* ClassName = "StartLevelMenu";
			StartLevelMenu(lib::draw::SceneNode *parent, lib::str_const &&name);
			virtual ~StartLevelMenu();

		private:
			lib::Configuration _gameConfig;
		};
	}
}

#endif