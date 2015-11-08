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
		Player(const lib::vector2du32 &bPosition, const lib::vector2df &size);
		virtual ~Player();

		void setBoardPosition(const lib::vector2du32 &np);
		inline lib::vector2du32 boardPosition() const { return _boardPosition; }

		inline const Direction &currentDirection() const { return playerDirection; }
		inline void setCurrentDirection(const Direction &nv) { playerDirection = nv; }

	private:
		void updateGraphicalDirection();

		lib::vector2du32 _boardPosition;
		Direction playerDirection;
	};
}

#endif
