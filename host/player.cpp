#include "player.hpp"

namespace zoper
{
	Player::Player(std::string name, SceneNode *parent, lib::vector2du32 bPosition, const lib::Rectf32 &box)
		: GameBaseTile{ std::move(name), parent, 0, box, 3 },
		boardPosition{ bPosition }, currentDirection{ Direction::Up }
	{
		setColor(getColorForToken());
	}

	Player::~Player() = default;
}
