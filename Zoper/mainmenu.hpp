#ifndef __MAINMENU_HPP__
#define __MAINMENU_HPP__

#include "lib/menu/menustep.hpp"
#include "lib/menu/choosecontrol.hpp"
#include "lib/configuration.hpp"

namespace zoper
{
	namespace zmenu
	{
		class MainMenu : public lib::menu::MenuStep
		{
		public:
			MainMenu();
			virtual ~MainMenu();

			virtual void onCreate() override;

		private:
			lib::Configuration _gameConfig;
			lib::sptr<lib::scn::draw::Renderizable> _logo{ nullptr };
			lib::sptr<lib::menu::ChooseControl> _chooseControl{ nullptr };

		};
	}
}

#endif
