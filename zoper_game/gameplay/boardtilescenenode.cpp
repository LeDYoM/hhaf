#include "boardtilescenenode.hpp"
#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace zoper
{
using namespace haf::scene;

BoardTileSceneNode::~BoardTileSceneNode() = default;

void BoardTileSceneNode::configure(const mtps::Rectf32& tileBox)
{
    LogAsserter::log_assert(m_pointInCenter == nullptr,
                "Point in center already initialized");
    LogAsserter::log_assert(background_tile_ == nullptr,
                "Background tile already initialized");

    createBackgroundTile(tileBox);
}

void BoardTileSceneNode::createBackgroundTile(const mtps::Rectf32& tileBox)
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

    background_tile_ = renderizableBuilder()
                           .name("backgroundTile")
                           .figType(FigType_t::Quad)
                           .box(tileBox)
                           .create();
}

void BoardTileSceneNode::setTileColor(Color color)
{
    LogAsserter::log_assert(background_tile_ != nullptr,
                            "This node is not correctly initialized");
    background_tile_->color = std::move(color);
}

}  // namespace zoper