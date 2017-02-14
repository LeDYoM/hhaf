#include "player.hpp"

namespace zoper
{
	Player::Player(const lib::draw::SceneNodeSPtr &parent, lib::str_const name, lib::vector2du32 bPosition, const lib::Rectf32 &box)
		: GameBaseTile{ parent, std::move(name), 0, box, 3 },
		boardPosition{ bPosition }, currentDirection{ Direction::Up }
	{
		m_sceneNode->setColor(getColorForToken());
	}

	Player::~Player() = default;
}
