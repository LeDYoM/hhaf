#ifndef HAF_SCENE_NODES_SCENENODETEXT_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENENODETEXT_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/types/property_group.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/scene/color.hpp>

namespace haf::scene::nodes
{

enum class AlignmentXModes : htps::u8
{
    Left = 0,
    Center,
    Right
};

enum class AlignmentYModes : htps::u8
{
    Top = 0,
    Middle,
    Bottom
};

struct Text
{
    using value_type = htps::str;
};

struct Font
{
    using value_type = htps::sptr<res::IFont>;
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
    using value_type = htps::vector2df;
};

using SceneNodeTextProperties = types::
    PropertyGroup<Text, Font, TextColor, AlignmentX, AlignmentY, AlignmentSize>;

}  // namespace haf::scene::nodes

#endif
