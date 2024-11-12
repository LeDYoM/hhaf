HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLE_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <facil_math/include/rect.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/types/scene_types.hpp>
#include <haf/include/scene/color.hpp>

namespace haf::res
{
class IShader;
class ITexture;
}  // namespace haf::res

namespace haf::render
{
enum class FigType_t : htps::u8;
class Renderizables;
}  // namespace haf::render

namespace haf::render
{
struct RenderizableData
{
    prop::PropertyState<htps::str> RenderizableName;
    prop::PropertyState<FigType_t> FigureTypeProperty;
    prop::PropertyState<scene::Color> ColorProperty;
    prop::PropertyState<htps::size_type> PointCount;
    prop::PropertyState<htps::sptr<res::IShader>> ShaderProperty;
    prop::PropertyState<htps::sptr<res::ITexture>> TextureProperty;
    prop::PropertyState<fmath::Rects32> TextureRectProperty;
};

}  // namespace haf::render

#endif
