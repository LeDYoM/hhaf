#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "gamebasetile.hpp"
#include "direction.hpp"

namespace zoper
{
	class Player : public GameBaseTile
	{
	public:
		Player(lib::vector2du32 bPosition, lib::vector2df size);
		virtual ~Player();

		lib::Property<lib::vector2du32> boardPosition;
		lib::Property<Direction> currentDirection;
	};
}

#endif
