#include "boardscenenode.hpp"

#include <lib/include/liblog.hpp>

#include <lib/scene/components/renderizables.hpp>

namespace zoper
{
	using namespace lib::scene;

	BoardSceneNode::BoardSceneNode(SceneNode* parent, str name, const Rectf32 &tileBox) :
		BaseClass{ parent, std::move(name) }, 
        m_pointInCenter{createSceneNode<RenderizableSceneNode>("backgroundTilePoint")}
	{
        auto renderizables = addComponentOfType<Renderizables>();
        m_backgroundTile = renderizables->createNode("backgroundTile");
        m_backgroundTile->figType.set(FigType_t::Quad);
        m_backgroundTile->pointCount.set(6U);
		m_backgroundTile->box.set(tileBox);

		// Size of the point in the middle of the tile
		static constexpr vector2df centerPointSize{ 15,15 };

        const Rectf32 b{ tileBox.center() - (centerPointSize / 2), centerPointSize };
        m_pointInCenter->node()->figType.set(FigType_t::Quad);
        m_pointInCenter->node()->pointCount.set(6U);
        m_pointInCenter->position.set(b.leftTop());
		m_pointInCenter->node()->box = { 0,0,b.width,b.height };
		m_pointInCenter->node()->color = colors::White;
	}

	BoardSceneNode::~BoardSceneNode() = default;

	void BoardSceneNode::setTileColor(Color color)
	{
		log_assert(m_backgroundTile != nullptr, "This node is not correctly initialized");
		m_backgroundTile->color = std::move(color);

	}
}