#include "boardtilescene_node.hpp"
#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizables.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::render;

namespace zoper
{
BoardTileSceneNode::~BoardTileSceneNode() = default;

void BoardTileSceneNode::onCreated()
{
    point_in_center_ =
        createSceneNode<RenderizableSceneNode>("backgroundTilePoint");

    point_in_center_->renderizableBuilder()
        .name("backgroundTilePoint")
        .figType(FigType_t::Sprite)
        .color(colors::White)
        .create();

    // Size of the point in the middle of the tile
    point_in_center_->Scale = {0.1F, 0.1F};

    background_tile_ = renderizableBuilder()
                           .name("backgroundTile")
                           .figType(FigType_t::Sprite)
                           .create();
}

void BoardTileSceneNode::update()
{
    BaseClass::update();

    if (BackgroundColor.readResetHasChanged())
    {
        background_tile_->material().color = BackgroundColor();
    }
}

}  // namespace zoper