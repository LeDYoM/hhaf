HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLE_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/property_group.hpp>

#include <haf/include/types/scene_types.hpp>
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
enum class FigType_t : htps::u8;
class Renderizables;
}  // namespace haf::render

namespace haf::render
{
struct RenderizableName : htps::BasicPropertyBase<htps::str>
{};

struct FigureTypeProperty : htps::PropertyStateBase<FigType_t>
{};

struct ColorProperty : htps::PropertyStateBase<scene::Color>
{};

struct PointCount : htps::PropertyStateBase<htps::size_type>
{};

struct ShaderProperty : htps::PropertyStateBase<htps::sptr<res::IShader>>
{};

struct TextureProperty : htps::PropertyStateBase<htps::sptr<res::ITexture>>
{};

struct TextureRectProperty : htps::PropertyStateBase<htps::Rects32>
{};

using RenderizableData = htps::PropertyGroup<RenderizableName,
                                             FigureTypeProperty,
                                             ColorProperty,
                                             PointCount,
                                             ShaderProperty,
                                             TextureProperty,
                                             TextureRectProperty>;
}  // namespace haf::render

#endif
