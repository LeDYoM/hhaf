#ifndef __LIB_IMENUCONTROL_HPP__
#define __LIB_IMENUCONTROL_HPP__

#include <lib/draw/rendergroup.hpp>
#include <SFML/Window/Event.hpp>

namespace lib
{
	namespace menu
	{
		class IMenuControl : public lib::scn::draw::RenderGroup
		{
		public:

			IMenuControl(const std::string &name) : lib::scn::draw::RenderGroup(name) {}
			virtual ~IMenuControl() {}
			virtual void onKeyPressed(sf::Event::KeyEvent kEvent) = 0;
			virtual void onKeyReleased(sf::Event::KeyEvent kEvent) = 0;

		};
	}
}

#endif
