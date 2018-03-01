#include "boardscenenode.hpp"

namespace zoper
{
	using namespace lib::scene;
	using namespace lib::scene::nodes;

	BoardSceneNode::BoardSceneNode(SceneNode* parent, str name, const Rectf32 &tileBox) :
		BaseClass{ parent, std::move(name) }, 
		m_backgroundTile(createRenderizable<NodeQuad>("backgroundTile")),
		m_pointInCenter(createRenderizable<NodeShape>("backgroundTilePoint", 30))
	{
		m_backgroundTile->box = tileBox;

		// Size of the point in the middle of the tile
		static constexpr vector2df centerPointSize{ 15,15 };

		m_pointInCenter->box = { tileBox.center() - (centerPointSize / 2), centerPointSize };
		m_pointInCenter->color = colors::White;
	}

	BoardSceneNode::~BoardSceneNode() = default;

	void BoardSceneNode::setTileColor(scene::Color color)
	{
		assert_debug(m_backgroundTile != nullptr, "This node is not correctly initialized");
		m_backgroundTile->color = std::move(color);

	}
}