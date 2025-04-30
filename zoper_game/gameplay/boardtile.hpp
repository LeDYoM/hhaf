#ifndef ZOPER_BOARD_TILE_COMPONENT_INCLUDE_HPP
#define ZOPER_BOARD_TILE_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene_components/renderizables.hpp>
#include <haf/include/scene_components/renderizable.hpp>

namespace zoper
{
class BoardTile : public haf::scene::RenderizableGroupComponent
{
    using Base = haf::scene::RenderizableGroupComponent;

public:
    /**
     * @brief Inherit SceneNode constructors.
     */
    using Base::Base;

    haf::prop::PropertyState<haf::scene::Color> BackgroundColor;

    void onAttached() override;
    void update() override;

private:
    htps::sptr<haf::render::Renderizable> m_background_tile;
    htps::sptr<haf::scene::Renderizable> m_point_in_center;
};
}  // namespace zoper

#endif