#include <haf/include/scene_nodes/scene_node_text_quad.hpp>

using namespace fmath;

namespace haf::scene::nodes
{
void TextQuad::onCreated()
{
    onTableNodeCreated += make_function(this, &TextQuad::onElementCreated);
    TableSize = {2U, 2U};
}

void TextQuad::onElementCreated(fmath::vector2dst index,
                                htps::sptr<SceneNodeText> const& node)
{
    if (index == vector2dst{0U, 0U})
    {
        // First text is left aligned on top
        node->AlignmentX = SceneNodeText::AlignmentXModes::Left;
        node->AlignmentY = SceneNodeText::AlignmentYModes::Top;
    }
    else if (index == vector2dst{1U, 0U})
    {
        // Second text is right aligned op top
        node->AlignmentX = SceneNodeText::AlignmentXModes::Left;
        node->AlignmentY = SceneNodeText::AlignmentYModes::Top;
    }
    else if (index == vector2dst{0U, 1U})
    {
        // Third text is left aligned on bottom
        node->AlignmentX = SceneNodeText::AlignmentXModes::Left;
        node->AlignmentY = SceneNodeText::AlignmentYModes::Top;
    }
    else if (index == vector2dst{1U, 1U})
    {
        // Fourth text is right aligned on bottom
        node->AlignmentX = SceneNodeText::AlignmentXModes::Left;
        node->AlignmentY = SceneNodeText::AlignmentYModes::Top;
    }
}

}  // namespace haf::scene::nodes
