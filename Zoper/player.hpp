#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "lib/board/itilescontroller.hpp"
#include "lib/scn/draw/renderizable.hpp"

#include "keymapping.hpp"
#include "direction.hpp"

namespace zoper
{
	class Player : public lib::board::ITile, public lib::scn::draw::Renderizable, public KeyMapping
	{
	public:
		Player(const lib::vector2du32 &bPosition, const lib::vector2df &size, const lib::Rect &centerRect);
		virtual ~Player();

		void setBoardPosition(const lib::vector2du32 &np);
		inline lib::vector2du32 boardPosition() const { return _boardPosition; }

		virtual bool onKeyPressed(sf::Event::KeyEvent kEvent);
		virtual bool onKeyReleased(sf::Event::KeyEvent kEvent);

		bool move(const Direction &d);

	private:
		void updateGraphicalDirection();

		lib::vector2du32 _boardPosition;
		lib::Rect _centerRect;
		Direction playerDirection;
	};
}

#endif
