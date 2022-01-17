#include "boardtilescene_node.hpp"
#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizables.hpp>

using namespace htps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::render;

BoardTileSceneNode::~BoardTileSceneNode() = default;

void BoardTileSceneNode::createBackgroundTile(const htps::Rectf32& tileBox)
{
    // Size of the point in the middle of the tile
    static constexpr vector2df centerPointSize{15, 15};

    const Rectf32 point_box{tileBox.center() - (centerPointSize / 2.0F),
                            centerPointSize};

    if (point_in_center_)
    {
        auto const result = removeSceneNode(point_in_center_);
        point_in_center_.reset();
        LogAsserter::log_assert(result);
    }

    point_in_center_ =
        createSceneNode<RenderizableSceneNode>("backgroundTilePoint");

    point_in_center_->renderizableBuilder()
        .name("backgroundTilePoint")
        .figType(FigType_t::Quad)
        .box(Rectf32{0, 0, point_box.width, point_box.height})
        .color(colors::White)
        .create();

    point_in_center_->prop<Position>().set(point_box.leftTop());

    background_tile_ = renderizableBuilder()
                           .name("backgroundTile")
                           .figType(FigType_t::Quad)
                           .box(tileBox)
                           .create();
}

void BoardTileSceneNode::update()
{
    if (prop<NodeSize>().readResetHasChanged())
    {
        LogAsserter::log_assert(point_in_center_ == nullptr,
                                "Point in center already initialized");
        LogAsserter::log_assert(background_tile_ == nullptr,
                                "Background tile already initialized");

        createBackgroundTile(prop<NodeSize>().get());
        prop<BackgroundColor>().setChanged();
    }

    if (prop<BackgroundColor>().readResetHasChanged())
    {
        background_tile_->prop<ColorProperty>() =
            std::move(prop<BackgroundColor>().get());
    }
}

}  // namespace zoper