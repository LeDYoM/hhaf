#include "menustep.hpp"
#include "menumanager.hpp"

namespace lib
{
	namespace menu
	{
		MenuControl::MenuControl(const std::string &name)
			: RenderGroup(name)
		{
		}


		MenuControl::~MenuControl()
		{
		}

		MenuManager * MenuControl::menuManager()
		{
			return dynamic_cast<MenuManager*>(parent());
		}

		void MenuControl::setMenuControl(sptr<IMenuControl> nControl)
		{
			addRenderGroup(nControl);
			m_control = nControl;
		}
	}
}
