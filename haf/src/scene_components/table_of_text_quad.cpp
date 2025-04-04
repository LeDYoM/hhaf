#include <haf/include/scene_components/table_of_text_quad.hpp>

using namespace fmath;

namespace haf::scene
{
void TableOfTextQuad::onAttached()
{
    onTableNodeCreated +=
        make_function(this, &TableOfTextQuad::onElementCreated);
    TableSize = {2U, 2U};
}

void TableOfTextQuad::onElementCreated(fmath::vector2dst index,
                                       htps::sptr<Text> const& node)
{
    if (index == vector2dst{0U, 0U})
    {
        // First text is left aligned on top
        node->AlignmentX = Text::AlignmentXModes::Left;
        node->AlignmentY = Text::AlignmentYModes::Top;
    }
    else if (index == vector2dst{1U, 0U})
    {
        // Second text is right aligned op top
        node->AlignmentX = Text::AlignmentXModes::Left;
        node->AlignmentY = Text::AlignmentYModes::Top;
    }
    else if (index == vector2dst{0U, 1U})
    {
        // Third text is left aligned on bottom
        node->AlignmentX = Text::AlignmentXModes::Left;
        node->AlignmentY = Text::AlignmentYModes::Top;
    }
    else if (index == vector2dst{1U, 1U})
    {
        // Fourth text is right aligned on bottom
        node->AlignmentX = Text::AlignmentXModes::Left;
        node->AlignmentY = Text::AlignmentYModes::Top;
    }
}

}  // namespace haf::scene
