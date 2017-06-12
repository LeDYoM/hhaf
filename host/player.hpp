#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <mtypes/include/types.hpp>
#include <lib/board/boardmodel.hpp>
#include <functional>

namespace zoper
{
	class Player : public GameBaseTile
	{
	public:
		Player(lib::scene::SceneNode* const parent, lib::str&& name, lib::vector2du32 bPosition, const lib::Rectf32 &box, lib::vector2df board2SceneFactor);
		virtual ~Player();

		lib::Property<lib::vector2du32> boardPosition;
		lib::Property<Direction> currentDirection;

		void movePlayer(const Direction &direction, const std::function<bool(const lib::vector2du32&)> &pointInCenter, const lib::sptr<lib::board::BoardModelComponent> &boardModel);
		void updateDirection();

	private:
		lib::scene::SceneNodeSPtr m_extraSceneNode;
		lib::scene::SceneNodeSPtr m_extraSceneNode_2;
		lib::vector2df m_board2SceneFactor;
	};
}

#endif