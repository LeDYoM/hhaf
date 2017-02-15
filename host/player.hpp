#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "gamebasetile.hpp"
#include "direction.hpp"

namespace zoper
{
	class Player : public GameBaseTile
	{
	public:
		Player(const lib::draw::SceneNodeSPtr &parent, lib::str_const name, lib::vector2du32 bPosition, const lib::Rectf32 &box, lib::vector2df board2SceneFactor);
		virtual ~Player();

		lib::Property<lib::vector2du32> boardPosition;
		lib::Property<Direction> currentDirection;

	public:
		lib::draw::SceneNodeSPtr m_rotateSceneNode;
		lib::vector2df m_board2SceneFactor;
	};
}

#endif
