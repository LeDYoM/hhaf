#include "player.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	Player::Player(SceneNode* const parent, str&& name, vector2du32 bPosition, const Rectf32 &box, vector2df board2SceneFactor)
		: GameBaseTile{ parent, std::move(name), 0 },
		boardPosition{ std::move(bPosition), [this]() {
			this->position = { m_board2SceneFactor.x * boardPosition().x, m_board2SceneFactor.y * boardPosition().y }; }
		},
		currentDirection{ Direction::DirectionData::Up }, m_board2SceneFactor{ std::move(board2SceneFactor) }
	{
		m_extraSceneNode = createSceneNode("m_extraSceneNode");
		m_extraSceneNode_2 = m_extraSceneNode->createSceneNode("m_extraSceneNode_2");
		m_node = m_extraSceneNode_2->createRenderizable<nodes::NodeShape>("Node", 3);
		m_node->configure();

		m_node->box = box;
		m_node->pointCount = 3;
		m_node->color = getColorForToken();
	}

	Player::~Player() = default;

	void Player::movePlayer(const Direction & direction, const std::function<bool(const vector2du32&)> &pointInCenter, const sptr<board::BoardModelComponent>& boardModel)
	{
		CLIENT_ASSERT(direction.isValid(), "Invalid direction passed to move");
		currentDirection = direction;
		auto nPosition = direction.applyToVector(boardPosition());
		if (pointInCenter(nPosition)) {
			boardModel->moveTile(boardPosition(), nPosition);
			boardPosition = { nPosition.x, nPosition.y };
		}
		else {
			updateDirection();
		}
	}

	void Player::updateDirection()
	{
		const auto tileCenter(m_board2SceneFactor / 2.0f);
		m_extraSceneNode->rotateAround(tileCenter, currentDirection().angle());

		if (currentDirection().value() == Direction::DirectionData::Up ||
			currentDirection().value() == Direction::DirectionData::Down) {
			m_extraSceneNode_2->scaleAround(tileCenter, { 1, 1 });
		}
		else {
			m_extraSceneNode_2->scaleAround(tileCenter, { m_board2SceneFactor.y / m_board2SceneFactor.x, m_board2SceneFactor.x / m_board2SceneFactor.y });
		}
	}
}