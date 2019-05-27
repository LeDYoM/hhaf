#include "boardscenenode.hpp"

#include <logger/include/log.hpp>

#include <lib/scene/components/renderizables.hpp>

namespace zoper
{
	using namespace lib::scene;
	using namespace lib::scene::nodes;

	BoardSceneNode::BoardSceneNode(SceneNode* parent, str name, const Rectf32 &tileBox) :
		BaseClass{ parent, std::move(name) }, 
        m_pointInCenter{createSceneNode<RenderizableSceneNode>("backgroundTilePoint")}
	{
        auto renderizables = ensureComponentOfType<Renderizables>();
        m_backgroundTile = renderizables->createRenderizable<NodeQuad>("backgroundTile");
		m_backgroundTile->box = tileBox;

		// Size of the point in the middle of the tile
		static constexpr vector2df centerPointSize{ 15,15 };

        const Rectf32 b{ tileBox.center() - (centerPointSize / 2), centerPointSize };
        m_pointInCenter->position.set(b.leftTop());
		m_pointInCenter->node()->box = { 0,0,b.width,b.height };
		m_pointInCenter->node()->color = colors::White;
	}

	BoardSceneNode::~BoardSceneNode() = default;

	void BoardSceneNode::setTileColor(Color color)
	{
		assert_debug(m_backgroundTile != nullptr, "This node is not correctly initialized");
		m_backgroundTile->color = std::move(color);

	}
}