#include <haf/include/scene_nodes/scene_node_letter.hpp>
#include <haf/include/scene/transformation_properties.hpp>
#include <haf/include/render/renderizables.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene::nodes
{
void SceneNodeLetter::setCharacterBox(Rectf32 const& characterBox,
                                      vector2df const& characterSize)
{
    prop<Position>().set(characterBox.leftTop());
    prop<Scale>().set(characterSize);
}

void SceneNodeLetter::setCharacterTextureData(sptr<res::ITexture> texture,
                                              Rectf32 const& textureUV)
{
    node()->prop<render::TextureProperty>()     = texture;
    node()->prop<render::TextureRectProperty>() = textureUV;
}

}  // namespace haf::scene::nodes
