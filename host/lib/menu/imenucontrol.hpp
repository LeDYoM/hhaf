#ifndef __LIB_IMENUCONTROL_HPP__
#define __LIB_IMENUCONTROL_HPP__

#include <lib/draw/rendergroup.hpp>
#include <SFML/Window/Event.hpp>
#include "menumanager.hpp"

namespace lib
{
	namespace menu
	{
		class ChooseControl;
		class IMenuControl : public lib::scn::draw::RenderGroup
		{
		public:

			IMenuControl(const std::string &name) : lib::scn::draw::RenderGroup(name) {}
			virtual ~IMenuControl() {}

			virtual void onCreate() = 0;
			MenuManager *menuManager() const { return dynamic_cast<MenuManager*>(parent()); }
			void addChooseControl(sptr<ChooseControl>);
		};
	}
}

#endif
