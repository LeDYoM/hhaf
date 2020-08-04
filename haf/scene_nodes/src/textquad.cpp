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
        auto node  = createNodeAt({count % 2, count / 2},
                                 name() + "node_" + make_str(count));
        node->set<Font>(font);
        node->set<TextColor>(color);
    }

    // First text is left aligned on top
    {
        auto const& align(nodeAt({0U, 0U}));
        align->set<AlignmentSize>(size);
        align->set<AlignmentX>(AlignmentXModes::Left);
        align->set<AlignmentY>(AlignmentYModes::Top);
    }

    // Second text is right aligned op top
    {
        auto const& align(nodeAt({1U, 0U}));
        align->set<AlignmentSize>(size);
        align->set<AlignmentX>(AlignmentXModes::Right);
        align->set<AlignmentY>(AlignmentYModes::Top);
    }

    // Third text is left aligned on bottom
    {
        auto const& align(nodeAt({0U, 1U}));
        align->set<AlignmentSize>(size);
        align->set<AlignmentX>(AlignmentXModes::Left);
        align->set<AlignmentY>(AlignmentYModes::Bottom);
    }

    // Fourth text is right aligned on bottom
    {
        auto const& align(nodeAt({1U, 1U}));
        align->set<AlignmentSize>(size);
        align->set<AlignmentX>(AlignmentXModes::Right);
        align->set<AlignmentY>(AlignmentYModes::Bottom);
    }
}

TextQuad::~TextQuad() = default;
}  // namespace haf::scene::nodes
