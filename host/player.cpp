#include "player.hpp"
#include "gamescene.hpp"

namespace zoper
{
	Player::Player(const lib::vector2du32 &bPosition, const lib::vector2df &size)
		: GameBaseTile{ 0, size, "player" },
		playerDirection{ Direction::Up }
	{
		setPointCount(3);
		setColor(getColorForToken());
		setBoardPosition(bPosition);
	}

	Player::~Player()
	{
	}

	void Player::setBoardPosition(const lib::vector2du32 &np)
	{
		_boardPosition = np;
	}

	void Player::setCurrentDirection(const Direction & direction)
	{
		playerDirection = direction;
	}
}
