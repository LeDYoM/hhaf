HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLE_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties/property_state.hpp>
#include <htypes/include/rect.hpp>
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
    htps::PropertyState<htps::str> RenderizableName;
    htps::PropertyState<FigType_t> FigureTypeProperty;
    htps::PropertyState<scene::Color> ColorProperty;
    htps::PropertyState<htps::size_type> PointCount;
    htps::PropertyState<htps::sptr<res::IShader>> ShaderProperty;
    htps::PropertyState<htps::sptr<res::ITexture>> TextureProperty;
    htps::PropertyState<htps::Rects32> TextureRectProperty;
};

}  // namespace haf::render

#endif
