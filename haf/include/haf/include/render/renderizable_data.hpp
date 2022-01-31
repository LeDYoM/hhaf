#ifndef HAF_RENDERIZABLE_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_DATA_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/types/scene_types.hpp>
#include <haf/include/types/property_group.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/scene/color.hpp>

namespace haf::res
{
class IShader;
class ITexture;
}  // namespace haf::res

namespace haf::render
{
struct RenderizableModifierContext;
enum class FigType_t : htps::u8;
class Renderizables;
}  // namespace haf::render

namespace haf::render
{
struct RenderizableName : BasicPropertyBase<types::str>
{};

struct FigureTypeProperty : PropertyStateBase<FigType_t>
{};

struct BoxProperty : PropertyStateBase<SceneBox>
{};

struct ColorProperty : PropertyStateBase<scene::Color>
{};

struct PointCount : PropertyStateBase<types::size_type>
{};

struct ShaderProperty : PropertyStateBase<types::sptr<res::IShader>>
{};

struct TextureProperty : PropertyStateBase<types::sptr<res::ITexture>>
{};

struct TextureRectProperty : PropertyStateBase<htps::Rects32>
{};

struct ColorModifierProperty
    : PropertyStateBase<
          function<scene::Color(const RenderizableModifierContext&)>>
{};

using RenderizableData = types::PropertyGroup<RenderizableName,
                                              FigureTypeProperty,
                                              BoxProperty,
                                              ColorProperty,
                                              PointCount,
                                              ShaderProperty,
                                              TextureProperty,
                                              TextureRectProperty,
                                              ColorModifierProperty>;
}  // namespace haf::render

#endif
