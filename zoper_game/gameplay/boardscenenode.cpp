#include "boardscenenode.hpp"

#include <lib/include/liblog.hpp>

#include <lib/scene/components/renderizables.hpp>

namespace zoper
{
using namespace lib::scene;

BoardSceneNode::BoardSceneNode(
    SceneNode *parent,
    str name,
    const Rectf32 &tileBox)
    : BaseClass{parent, std::move(name)}
{
    // Size of the point in the middle of the tile
    static constexpr vector2df centerPointSize{15, 15};

    const Rectf32 point_box{tileBox.center() - (centerPointSize / 2.0F), centerPointSize};

    m_pointInCenter =
        createSceneNode<RenderizableSceneNode>(
            "backgroundTilePoint", FigType_t::Quad,
            Rectf32{0, 0, point_box.width, point_box.height}, colors::White);
    m_pointInCenter->position.set(point_box.leftTop());

    auto renderizables = addComponentOfType<Renderizables>();
    m_backgroundTile = renderizables->createRenderizable("backgroundTile", FigType_t::Quad, tileBox);
}

BoardSceneNode::~BoardSceneNode() = default;

void BoardSceneNode::setTileColor(Color color)
{
    log_assert(m_backgroundTile != nullptr, "This node is not correctly initialized");
    m_backgroundTile->color = std::move(color);
}
} // namespace zoper