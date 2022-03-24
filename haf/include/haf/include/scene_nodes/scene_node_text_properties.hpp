#ifndef HAF_SCENE_NODE_TEXT_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_NODE_TEXT_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/types/property_group.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene/scene_node.hpp>
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

struct Text : PropertyStateBase<htps::str>
{};

struct Font : PropertyStateBase<htps::sptr<res::IFont>>
{};

struct TextColor : PropertyStateBase<Color>
{};

struct BaseSize : PropertyStateBase<htps::vector2df>
{};

struct BaseText : PropertyStateBase<htps::str>
{};

struct AlignmentX : PropertyStateBase<AlignmentXModes>
{};

struct AlignmentY : PropertyStateBase<AlignmentYModes>
{};

struct AlignmentSize : PropertyStateBase<htps::vector2df>
{};

using SceneNodeTextProperties = types::PropertyGroup<Text,
                                                     Font,
                                                     TextColor,
                                                     BaseSize,
                                                     BaseText,
                                                     AlignmentX,
                                                     AlignmentY,
                                                     AlignmentSize>;

}  // namespace haf::scene::nodes

#endif
