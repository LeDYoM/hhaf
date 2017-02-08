#include "player.hpp"

namespace zoper
{
	Player::Player(lib::vector2du32 bPosition, const lib::Rectf32 &box)
		: GameBaseTile{ 0, box, "player",3 },
		boardPosition{ bPosition }, currentDirection{ Direction::Up }
	{
		setColor(getColorForToken());
	}

	Player::~Player() = default;
}
