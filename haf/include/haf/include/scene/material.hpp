HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_MATERIAL_INCLUDE_HPP
#define HAF_SCENE_MATERIAL_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/properties/property_state.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/haf_export.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>

namespace haf::scene
{

class HAF_API Material
{
public:
    htps::PropertyState<scene::Color> color;
    htps::PropertyState<htps::sptr<res::IShader>> shader;
    htps::PropertyState<htps::sptr<res::ITexture>> texture;
    htps::PropertyState<htps::Rects32> textureRect;
};
}  // namespace haf::scene

#endif
