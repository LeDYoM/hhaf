#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "gamebasetile.hpp"
#include "direction.hpp"

namespace zoper
{
	class Player : public GameBaseTile
	{
	public:
		Player(const lib::vector2du32 &bPosition, const lib::vector2df &size);
		virtual ~Player();

		void setBoardPosition(const lib::vector2du32 &np);
		inline lib::vector2du32 boardPosition() const { return _boardPosition; }

		inline const Direction &currentDirection() const { return playerDirection; }
		void setCurrentDirection(const Direction &nv);

	private:
		lib::vector2du32 _boardPosition;
		Direction playerDirection;
	};
}

#endif
