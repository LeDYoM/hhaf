#ifndef LIB_MENU_MENUCONTROL_INCLUDE_HPP__
#define LIB_MENU_MENUCONTROL_INCLUDE_HPP__

#include <lib/draw/rendergroup.hpp>
#include <lib/menu/imenucontrol.hpp>
#include <lib/include/types.hpp>

#include <vector>
#include <memory>

namespace lib
{
	namespace menu
	{
		class MenuManager;
		class MenuControl : public scn::draw::RenderGroup
		{
		public:
			MenuControl(const std::string &name);
			virtual ~MenuControl();

			virtual void onCreate() = 0;
			MenuManager *menuManager();

			void setMenuControl(sptr<IMenuControl> nControl);

		private:
			sptr<IMenuControl> m_control;
		};
	}
}

#endif
