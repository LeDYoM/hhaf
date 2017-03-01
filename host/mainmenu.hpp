#ifndef __MAINMENU_HPP__
#define __MAINMENU_HPP__

#include <lib/gui/choosecontrolgroup.hpp>
#include <lib/core/configuration.hpp>
#include <lib/draw/scenenode.hpp>

namespace zoper
{
	namespace zmenu
	{
		class MainMenu : public lib::gui::ChooseControlGroup
		{
		public:
			constexpr static char* ClassName = "MainMenu";
			MainMenu(lib::draw::SceneNode *parent, lib::str_const&& name);
			virtual ~MainMenu();

		private:
			lib::Configuration m_gameConfig;
			lib::sptr<lib::gui::ChooseControl> m_chooseControl;
		};
	}
}

#endif
