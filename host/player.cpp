#include "player.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::draw;

	Player::Player(const SceneNodeSPtr &parent, str_const name, vector2du32 bPosition, const Rectf32 &box, vector2df board2SceneFactor)
		: GameBaseTile{ parent, std::move(name), 0 },
		boardPosition{ std::move(bPosition), [this]() { 
			this->position = { m_board2SceneFactor.x * boardPosition().x, m_board2SceneFactor.y * boardPosition().y }; } 
		},
		currentDirection{ Direction::Up }, m_board2SceneFactor{ std::move(board2SceneFactor) }
	{
		m_extraSceneNode = m_sceneNode->createSceneNode("m_extraSceneNode");
		m_extraSceneNode_2 = m_extraSceneNode->createSceneNode("sdafasfd");
		m_node = m_extraSceneNode_2->createRenderizable<nodes::NodeShape>("Node", box, nullptr, 3, colors::White);
		m_sceneNode->setColor(getColorForToken());
	}

	Player::~Player() = default;
}
