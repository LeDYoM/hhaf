#include "scene_node_letter.hpp"
#include <haf/include/render/renderizables.hpp>

using namespace htps;

namespace haf::scene::nodes
{
void SceneNodeLetter::setCharacterTextureData(sptr<res::ITexture> texture,
                                              Rectf32 const& textureUV)
{
    node()->TextureProperty     = texture;
    node()->TextureRectProperty = textureUV;
}

}  // namespace haf::scene::nodes
