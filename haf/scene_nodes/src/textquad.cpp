#include "textquad.hpp"

using namespace mtps;

namespace haf::scene::nodes
{
void TextQuad::configure(mtps::sptr<res::IFont> font,
                         const Color& color,
                         const mtps::vector2df& size)
{
    setTableSize({2, 2});
    for (size_type count{0}; count < 4U; ++count)
    {
        auto node = createNodeAt({count % 2, count / 2},
                                 name() + "node_" + make_str(count));
        node->put<Font>(font).put<TextColor>(color);
    }

    // First text is left aligned on top
    {
        nodeAt({0U, 0U})
            ->put<AlignmentSize>(size)
            .put<AlignmentX>(AlignmentXModes::Left)
            .put<AlignmentY>(AlignmentYModes::Top);
    }

    // Second text is right aligned op top
    {
        nodeAt({1U, 0U})
            ->put<AlignmentSize>(size)
            .put<AlignmentX>(AlignmentXModes::Right)
            .put<AlignmentY>(AlignmentYModes::Top);
    }

    // Third text is left aligned on bottom
    {
        nodeAt({0U, 1U})
            ->put<AlignmentSize>(size)
            .put<AlignmentX>(AlignmentXModes::Left)
            .put<AlignmentY>(AlignmentYModes::Bottom);
    }

    // Fourth text is right aligned on bottom
    {
        nodeAt({1U, 1U})
            ->put<AlignmentSize>(size)
            .put<AlignmentX>(AlignmentXModes::Right)
            .put<AlignmentY>(AlignmentYModes::Bottom);
    }
}

TextQuad::~TextQuad() = default;
}  // namespace haf::scene::nodes
