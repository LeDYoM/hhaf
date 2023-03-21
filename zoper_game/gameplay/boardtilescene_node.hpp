#ifndef ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP
#define ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene_nodes/renderizables_scene_node.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>

namespace zoper
{
class BoardTileSceneNode : public haf::scene::RenderizablesSceneNode
{
    using BaseClass = haf::scene::RenderizablesSceneNode;

public:
    /**
     * @brief Inherit SceneNode constructors.
     */
    using BaseClass::BaseClass;

    prop::PropertyState<haf::scene::Color> BackgroundColor;

    void onCreated() override;

    /**
     * @brief Destroy the Board Tile Scene Node object
     */
    ~BoardTileSceneNode() override;

    void update() override;

private:
    htps::sptr<haf::render::Renderizable> background_tile_;
    htps::sptr<haf::scene::RenderizableSceneNode> point_in_center_;
};
}  // namespace zoper

#endif