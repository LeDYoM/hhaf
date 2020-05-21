#include "boardscenenode.hpp"
#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace zoper
{
using namespace haf::scene;

BoardSceneNode::BoardSceneNode(SceneNode* parent,
                               str name,
                               const Rectf32& tileBox) :
    BaseClass{parent, std::move(name)}
{
    // Size of the point in the middle of the tile
    static constexpr vector2df centerPointSize{15, 15};

    const Rectf32 point_box{tileBox.center() - (centerPointSize / 2.0F),
                            centerPointSize};

    m_pointInCenter = createSceneNode<RenderizableSceneNode>(
        "backgroundTilePoint", FigType_t::Quad,
        Rectf32{0, 0, point_box.width, point_box.height}, colors::White);
    m_pointInCenter->position.set(point_box.leftTop());

    m_backgroundTile = renderizableBuilder()
                           .name("backgroundTile")
                           .figType(FigType_t::Quad)
                           .box(tileBox)
                           .create();
}

BoardSceneNode::~BoardSceneNode() = default;

void BoardSceneNode::setTileColor(Color color)
{
    LogAsserter::log_assert(m_backgroundTile != nullptr,
                            "This node is not correctly initialized");
    m_backgroundTile->color = std::move(color);
}
}  // namespace zoper