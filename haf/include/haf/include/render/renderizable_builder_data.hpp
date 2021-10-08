#ifndef HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP

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
struct RenderizableName
{
    using value_type = types::str;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

struct FigureTypeProperty
{
    using value_type = FigType_t;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

struct RenderizableSceneBoxProperty
{
    using value_type = SceneBox;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

struct ColorProperty
{
    using value_type = scene::Color;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

struct ShaderProperty
{
    using value_type = types::sptr<res::IShader>;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

struct TextureProperty
{
    using value_type = types::sptr<res::ITexture>;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

struct ColorModifierProperty
{
    using value_type =
        function<scene::Color(const RenderizableModifierContext&)>;

    struct UseCustomPropertyType
    {
        template <typename Tag>
        using PropertyType = htps::BasicProperty<typename Tag::value_type, Tag>;
    };
};

using RenderizableBuilderDataGroup =
    types::PropertyGroup<RenderizableName,
                         FigureTypeProperty,
                         RenderizableSceneBoxProperty,
                         ColorProperty,
                         Times,
                         Switch>;

struct RenderizableBuilderData
{
    htps::rptr<Renderizables> renderizables_;
    htps::str name_;
    FigType_t figType_;
    htps::Rectf32 box_{};
    scene::Color color_{scene::colors::White};
    htps::size_type pointCount_{4U};
    types::sptr<res::IShader> shader_{nullptr};
    types::sptr<res::ITexture> texture_{nullptr};
    function<scene::Color(const RenderizableModifierContext&)>
        color_modifier_{};
};

}  // namespace haf::render

#endif
