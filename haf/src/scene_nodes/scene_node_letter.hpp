HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_NODES_SCENE_NODE_LETTER_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENE_NODE_LETTER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties/iproperty.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include "resources/character_render_data.hpp"

namespace haf::scene::nodes
{
class SceneNodeLetter : public RenderizableSceneNode
{
    using BaseClass = RenderizableSceneNode;

public:
    using BaseClass::BaseClass;

    void setCharacterTextureData(htps::sptr<haf::res::ITexture> texture,
                                 htps::Rectf32 const& textureUV);
};

}  // namespace haf::scene::nodes

#endif
