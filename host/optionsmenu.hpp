#ifndef __OPTIONSMENU_HPP__
#define __OPTIONSMENU_HPP__

#include <lib/menu/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class OptionsMenu : public lib::menu::ChooseControl, public lib::Configuration
		{
		public:
			OptionsMenu(lib::menu::MenuManager *parent);
			virtual ~OptionsMenu();
			virtual void onAddedToScene() override;
		};
	}
}

#endif
