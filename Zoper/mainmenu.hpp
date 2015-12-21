#ifndef __MAINMENU_HPP__
#define __MAINMENU_HPP__

#include "lib/menu/menustep.hpp"

namespace zoper
{
	namespace menu
	{
		class MainMenu : public lib::menu::MenuStep
		{
		public:
			MainMenu();
			virtual ~MainMenu();

			virtual void onCreate() override;

		private:
			lib::sptr<lib::scn::draw::Renderizable> _logo{ nullptr };

		};
	}
}

#endif
