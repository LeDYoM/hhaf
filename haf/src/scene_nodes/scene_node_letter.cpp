#include "scene_node_letter.hpp"
#include <haf/include/scene/transformation_properties.hpp>
#include <haf/include/render/renderizables.hpp>

using namespace htps;

namespace haf::scene::nodes
{
/*
void SceneNodeLetter::setCharacterBox(Rectf32 const& characterBox)
{
    prop<Position>().set(characterBox.leftTop() - (characterBox.size() / 2.0F));
    prop<Scale>().set(characterBox.size());
}
*/

void SceneNodeLetter::update()
{
    BaseClass::update();
    if (character_render_data.readResetHasChanged())
    {
        
    }
}

void SceneNodeLetter::setCharacterTextureData(sptr<res::ITexture> texture,
                                              Rectf32 const& textureUV)
{
    node()->prop<render::TextureProperty>()     = texture;
    node()->prop<render::TextureRectProperty>() = textureUV;
}

}  // namespace haf::scene::nodes
