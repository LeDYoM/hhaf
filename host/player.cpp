#include "player.hpp"

namespace zoper
{
	Player::Player(SceneNode *parent, std::string name, lib::vector2du32 bPosition, const lib::Rectf32 &box)
		: GameBaseTile{ parent, std::move(name), 0, box, 3 },
		boardPosition{ bPosition }, currentDirection{ Direction::Up }
	{
		setColor(getColorForToken());
	}

	Player::~Player() = default;
}
