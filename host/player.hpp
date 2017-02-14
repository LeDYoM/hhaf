#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "gamebasetile.hpp"
#include "direction.hpp"

namespace zoper
{
	class Player : public GameBaseTile
	{
	public:
		Player(const lib::draw::SceneNodeSPtr &parent, lib::str_const name, lib::vector2du32 bPosition, const lib::Rectf32 &box);
		virtual ~Player();

		lib::Property<lib::vector2du32> boardPosition;
		lib::Property<Direction> currentDirection;
	};
}

#endif
