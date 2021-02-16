#ifndef HAF_SCENE_NODES_SCENENODETEXT_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENENODETEXT_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/grouping_property.hpp>
#include <haf/resources/include/ifont.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/color.hpp>

namespace haf::scene::nodes
{

enum class AlignmentXModes : mtps::u8
{
    Left = 0,
    Center,
    Right
};

enum class AlignmentYModes : mtps::u8
{
    Top = 0,
    Middle,
    Bottom
};

struct Text
{
    using value_type = mtps::str;
};

struct Font
{
    using value_type = mtps::sptr<res::IFont>;
};

struct TextColor
{
    using value_type = Color;
};

struct AlignmentX
{
    using value_type = AlignmentXModes;
};

struct AlignmentY
{
    using value_type = AlignmentYModes;
};

struct AlignmentSize
{
    using value_type = mtps::vector2df;
};

using SceneNodeTextProperties = mtps::
    PropertyGroup<Text, Font, TextColor, AlignmentX, AlignmentY, AlignmentSize>;

}  // namespace haf::scene::nodes

#endif
