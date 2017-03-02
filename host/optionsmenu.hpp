#ifndef __OPTIONSMENU_HPP__
#define __OPTIONSMENU_HPP__

#include <lib/gui/choosecontrol.hpp>
#include <lib/core/configuration.hpp>

namespace zoper
{
	namespace zmenu
	{
		class OptionsMenu : public lib::gui::ChooseControl, public lib::Configuration
		{
		public:
			constexpr static char* ClassName = "OptionsMenu";

			OptionsMenu(lib::draw::SceneNode *parent, lib::str_const &&name);
			virtual ~OptionsMenu();
		};
	}
}

#endif
