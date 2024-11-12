HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_NODES_SCENE_NODE_TEXT_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENE_NODE_TEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/properties/iproperty.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/scene_nodes/text_base_size.hpp>

namespace haf::scene::nodes
{
class SceneNodeText : public TransformableSceneNode
{
    using BaseClass = TransformableSceneNode;

public:
    /**
     * @brief Constructor
     */
    using BaseClass::BaseClass;

    void onCreated() override;

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

    prop::PropertyState<htps::str> Text;
    prop::PropertyState<htps::sptr<res::IFont>> Font;
    prop::PropertyState<Color> TextColor;
    prop::PropertyState<TextBaseSize> TextBaseSizeProperty;
    prop::PropertyState<AlignmentXModes> AlignmentX;
    prop::PropertyState<AlignmentYModes> AlignmentY;
    prop::PropertyState<fmath::vector2df> AlignmentSize;

protected:
    void update() override final;
    htps::sptr<TransformableSceneNode> m_inner_scale_scene_node;
    htps::sptr<TransformableSceneNode> m_inner_position_scene_node;
    htps::sptr<TransformableSceneNode> m_letters_scene_node;
};

}  // namespace haf::scene::nodes

#endif
