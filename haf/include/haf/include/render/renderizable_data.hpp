#ifndef HAF_RENDERIZABLE_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_DATA_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
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

struct FigureTypeProperty : BasicPropertyBase<FigType_t>
{};

struct RenderizableSceneBoxProperty : BasicPropertyBase<SceneBox>
{};

struct ColorProperty : BasicPropertyBase<scene::Color>
{};

struct PointCount : BasicPropertyBase<types::size_type>
{};

struct ShaderProperty : BasicPropertyBase<types::sptr<res::IShader>>
{};

struct TextureProperty : BasicPropertyBase<types::sptr<res::ITexture>>
{};

struct ColorModifierProperty
    : BasicPropertyBase<
          function<scene::Color(const RenderizableModifierContext&)>>
{};

using RenderizableData = types::PropertyGroup<RenderizableName,
                                              FigureTypeProperty,
                                              RenderizableSceneBoxProperty,
                                              ColorProperty,
                                              PointCount,
                                              ShaderProperty,
                                              TextureProperty,
                                              ColorModifierProperty>;
}  // namespace haf::render

#endif
