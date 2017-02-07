#include "player.hpp"

namespace zoper
{
	Player::Player(lib::vector2du32 bPosition, lib::vector2df size)
		: GameBaseTile{ 0, size, "player",3 },
		boardPosition{ bPosition }, currentDirection{ Direction::Up }
	{
		color.set(getColorForToken());
	}

	Player::~Player() = default;
}
