HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_NODE_TEXT_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_NODE_TEXT_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/property_group.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/scene_nodes/text_base_size.hpp>

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

struct Text : htps::PropertyStateBase<htps::str>
{};

struct Font : htps::PropertyStateBase<htps::sptr<res::IFont>>
{};

struct TextColor : htps::PropertyStateBase<Color>
{};

struct TextBaseSizeProperty : htps::PropertyStateBase<TextBaseSize>
{};

struct AlignmentX : htps::PropertyStateBase<AlignmentXModes>
{};

struct AlignmentY : htps::PropertyStateBase<AlignmentYModes>
{};

struct AlignmentSize : htps::PropertyStateBase<htps::vector2df>
{};

using SceneNodeTextProperties = htps::PropertyGroup<Text,
                                                    Font,
                                                    TextColor,
                                                    TextBaseSizeProperty,
                                                    AlignmentX,
                                                    AlignmentY,
                                                    AlignmentSize>;

}  // namespace haf::scene::nodes

#endif
