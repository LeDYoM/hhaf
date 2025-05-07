#include "boardtile.hpp"
#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizables.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::render;

namespace zoper
{
void BoardTile::onAttached()
{
    m_point_in_center = attachedNode()->createSceneNode("backgroundTile")
        ->component<scene::RenderizableGroupComponent>();
    m_point_in_center->renderizableBuilder()
        .name("backgroundTilePoint")
        .figType(FigType_t::Sprite)
        .color(colors::White)
        .create();

    // Size of the point in the middle of the tile
    m_point_in_center->attachedNode()->Scale = {0.1F, 0.1F};

//    auto tileRenderizable2{attachedNode()
//        ->createSceneNode("backgroundTilePoint")->component<scene::Renderizable>()};

//    m_background_tile = tileRenderizable2->renderizableBuilder()
//                            .name("backgroundTile")
//                            .figType(FigType_t::Sprite)
//                            .create();
}

void BoardTile::update()
{
    Base::update();

    if (BackgroundColor.readResetHasChanged())
    {
//        m_background_tile->material().color = BackgroundColor();
    }
}

}  // namespace zoper
