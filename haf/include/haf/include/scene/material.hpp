HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_MATERIAL_INCLUDE_HPP
#define HAF_SCENE_MATERIAL_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <facil_math/include/rect.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/haf_export.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>

namespace haf::scene
{

class HAF_API Material
{
public:
    prop::PropertyState<scene::Color> color;
    prop::PropertyState<htps::sptr<res::IShader>> shader;
    prop::PropertyState<htps::sptr<res::ITexture>> texture;
    prop::PropertyState<fmath::Rects32> textureRect;
};
}  // namespace haf::scene

#endif
