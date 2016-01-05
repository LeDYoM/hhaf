#ifndef __OPTIONSMENU_HPP__
#define __OPTIONSMENU_HPP__

#include "lib/menu/menustep.hpp"
#include "lib/menu/choosecontrol.hpp"
#include "lib/configuration.hpp"

namespace zoper
{
	namespace zmenu
	{
		class OptionsMenu : public lib::menu::MenuStep
		{
		public:
			OptionsMenu();
			virtual ~OptionsMenu();
			virtual void onCreate() override;

		private:
			lib::Configuration _gameConfig;
			lib::sptr<lib::menu::ChooseControl> _chooseControl{ nullptr };
		};
	}
}

#endif