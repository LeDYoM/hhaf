#include "boardtilescene_node.hpp"
#include "boardgroup.hpp"
#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizables.hpp>

using namespace htps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::render;

BoardTileSceneNode::~BoardTileSceneNode() = default;

void BoardTileSceneNode::updateBackgroundTile(vector2df const& tile_size)
{
    if (point_in_center_ == nullptr)
    {
        point_in_center_ =
            createSceneNode<RenderizableSceneNode>("backgroundTilePoint");

        point_in_center_->renderizableBuilder()
            .name("backgroundTilePoint")
            .figType(FigType_t::Sprite)
            .color(colors::White)
            .create();
    }

    // Size of the point in the middle of the tile
    vector2df centerPointSize{sceneViewSize() / 20.0F};
//    point_in_center_->prop<Position>().set(tile_size / 3.0F);
    point_in_center_->prop<Scale>().set({0.5F, 0.5F});

    if (background_tile_ == nullptr)
    {
        background_tile_ = renderizableBuilder()
                               .name("backgroundTile")
                               .figType(FigType_t::Sprite)
                               .create();
    }

    prop<Scale>() = tile_size;
}

void BoardTileSceneNode::update()
{
    BaseClass::update();
    if (ancestor<BoardGroup>()->prop<TableSizeForNodes>().hasChanged())
    {
        updateBackgroundTile(
            ancestor<BoardGroup>()->prop<TableSizeForNodes>().get());
    }

    if (prop<NodeSize>().readResetHasChanged())
    {
        prop<BackgroundColor>().setChanged();
    }

    if (prop<BackgroundColor>().readResetHasChanged())
    {
        background_tile_->prop<ColorProperty>() =
            std::move(prop<BackgroundColor>().get());
    }
}

}  // namespace zoper