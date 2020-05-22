#include "boardscenenode.hpp"
#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace zoper
{
using namespace haf::scene;

BoardSceneNode::~BoardSceneNode() = default;

void BoardSceneNode::configure(const mtps::Rectf32 &tileBox) 
{
    // Size of the point in the middle of the tile
    static constexpr vector2df centerPointSize{15, 15};

    const Rectf32 point_box{tileBox.center() - (centerPointSize / 2.0F),
                            centerPointSize};

    m_pointInCenter =
        createSceneNode<RenderizableSceneNode>("backgroundTilePoint");

    auto builder = m_pointInCenter->renderizableBuilder();
    builder.name("backgroundTilePoint")
        .figType(FigType_t::Quad)
        .box(Rectf32{0, 0, point_box.width, point_box.height})
        .color(colors::White);
    m_pointInCenter->buildNode(builder);

    m_pointInCenter->position.set(point_box.leftTop());

    m_backgroundTile = renderizableBuilder()
                           .name("backgroundTile")
                           .figType(FigType_t::Quad)
                           .box(tileBox)
                           .create();    
}

void BoardSceneNode::setTileColor(Color color)
{
    LogAsserter::log_assert(m_backgroundTile != nullptr,
                            "This node is not correctly initialized");
    m_backgroundTile->color = std::move(color);
}

}  // namespace zoper