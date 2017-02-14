#include "player.hpp"

namespace zoper
{
	using namespace lib;

	Player::Player(const draw::SceneNodeSPtr &parent, str_const name, vector2du32 bPosition, const Rectf32 &box, vector2df board2SceneFactor)
		: GameBaseTile{ parent, std::move(name), 0, box, 3 },
		boardPosition{ bPosition, [this]() { this->position = { m_board2SceneFactor.x * boardPosition().x, m_board2SceneFactor.y * boardPosition().y }; } },
		currentDirection{ Direction::Up }, m_board2SceneFactor{ std::move(board2SceneFactor) }
	{
		m_sceneNode->setColor(getColorForToken());
	}

	Player::~Player() = default;
}
