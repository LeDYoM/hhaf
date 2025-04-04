HTPS_PRAGMA_ONCE
#ifndef HAF_TEXT_COMPONENT_INCLUDE_HPP
#define HAF_TEXT_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/properties/iproperty.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/scene_nodes/text_base_size.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/properties/property_state.hpp>

namespace haf::scene
{
class Text : public component::Component
{
public:
    void onAttached() override;

    enum class AlignmentXModes : htps::u8
    {
        Left = 0U,
        Center,
        Right
    };

    enum class AlignmentYModes : htps::u8
    {
        Top = 0,
        Middle,
        Bottom
    };

    prop::PropertyState<htps::str> Text;
    prop::PropertyState<htps::sptr<res::IFont>> Font;
    prop::PropertyState<Color> TextColor;
    prop::PropertyState<nodes::TextBaseSize> TextBaseSizeProperty;
    prop::PropertyState<AlignmentXModes> AlignmentX;
    prop::PropertyState<AlignmentYModes> AlignmentY;
    prop::PropertyState<fmath::vector2df> AlignmentSize;

protected:
    void update() override final;
    htps::sptr<SceneNode> m_inner_scale_scene_node;
    htps::sptr<SceneNode> m_inner_position_scene_node;
    htps::sptr<SceneNode> m_letters_scene_node;
};

}  // namespace haf::scene

#endif
