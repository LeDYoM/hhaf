#include "boardtilescenenode.hpp"
#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizables.hpp>

using namespace htps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;

BoardTileSceneNode::~BoardTileSceneNode() = default;

void BoardTileSceneNode::createBackgroundTile(const htps::Rectf32& tileBox)
{
    // Size of the point in the middle of the tile
    static constexpr vector2df centerPointSize{15, 15};

    const Rectf32 point_box{tileBox.center() - (centerPointSize / 2.0F),
                            centerPointSize};

    if (m_pointInCenter)
    {
        auto const result = removeSceneNode(m_pointInCenter);
        m_pointInCenter.reset();
        LogAsserter::log_assert(result);
    }

    m_pointInCenter =
        createSceneNode<RenderizableSceneNode>("backgroundTilePoint");

    auto builder = m_pointInCenter->renderizables().renderizableBuilder();
    builder.name("backgroundTilePoint")
        .figType(FigType_t::Quad)
        .box(Rectf32{0, 0, point_box.width, point_box.height})
        .color(colors::White);
    m_pointInCenter->buildNode(builder);

    m_pointInCenter->prop<Position>().set(point_box.leftTop());

    background_tile_ = createRenderizables().renderizableBuilder()
                           .name("backgroundTile")
                           .figType(FigType_t::Quad)
                           .box(tileBox)
                           .create();
}

void BoardTileSceneNode::update()
{
    if (prop<NodeSize>().readResetHasChanged())
    {
        LogAsserter::log_assert(m_pointInCenter == nullptr,
                                "Point in center already initialized");
        LogAsserter::log_assert(background_tile_ == nullptr,
                                "Background tile already initialized");

        createBackgroundTile(prop<NodeSize>().get());
        prop<BackgroundColor>().setChanged();
    }

    if (prop<BackgroundColor>().readResetHasChanged())
    {
        background_tile_->color = std::move(
            prop<BackgroundColor>().get());
    }
}

}  // namespace zoper