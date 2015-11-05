#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "lib/board/itilescontroller.hpp"
#include "lib/scn/draw/renderizable.hpp"

#include "utils.hpp"

namespace zoper
{
	class Player : public lib::board::ITile, public lib::scn::draw::Renderizable, public KeyMapping
	{
	public:
		Player(lib::u32 x,lib::u32 y, const sf::Vector2f &size);
		virtual ~Player();

		void setBoardPosition(lib::u32 x, lib::u32 y);
		inline lib::u32 boardX() const { return _x; }
		inline lib::u32 boardY() const { return _y; }

		virtual bool onKeyPressed(sf::Event::KeyEvent kEvent);
		virtual bool onKeyReleased(sf::Event::KeyEvent kEvent);

	private:
		void updateGraphicalDirection();

		lib::u32 _x;
		lib::u32 _y;
		Direction playerDirection;
	};
}

#endif
