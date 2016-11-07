#ifndef __MAINMENU_HPP__
#define __MAINMENU_HPP__

#include <lib/menu/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class MainMenu : public lib::menu::IMenuControl
		{
		public:
			MainMenu(lib::scn::draw::RenderGroup *parent);
			virtual ~MainMenu();

			virtual void onCreate() override;

		private:
			lib::Configuration _gameConfig;
			lib::sptr<lib::menu::ChooseControl> _chooseControl{ nullptr };
		};
	}
}

#endif
