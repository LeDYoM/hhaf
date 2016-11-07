#ifndef __STARTLEVELMENU_HPP__
#define __STARTLEVELMENU_HPP__

#include <lib/menu/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class StartLevelMenu : public lib::menu::ChooseControl, public lib::Configuration
		{
		public:
			StartLevelMenu(lib::scn::draw::RenderGroup *parent);
			virtual ~StartLevelMenu();
			virtual void onAddedToScene() override;

		private:
			lib::Configuration _gameConfig;
		};
	}
}

#endif
