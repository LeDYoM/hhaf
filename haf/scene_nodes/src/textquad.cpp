#include "textquad.hpp"

using namespace mtps;

namespace haf::scene::nodes
{

TextQuad::~TextQuad() = default;

void TextQuad::onCreated()
{
    setTableSize({2, 2});
    for (size_type count{0}; count < 4U; ++count)
    {
        auto node = createNodeAt({count % 2U, count / 2U},
                                 name() + "node_" + make_str(count));
    }

    // First text is left aligned on top
    {
        nodeAt({0U, 0U})
            ->prop<SceneNodeTextProperties>()
            .put<AlignmentX>(AlignmentXModes::Left)
            .put<AlignmentY>(AlignmentYModes::Top);
    }

    // Second text is right aligned op top
    {
        nodeAt({1U, 0U})
            ->prop<SceneNodeTextProperties>()
            .put<AlignmentX>(AlignmentXModes::Right)
            .put<AlignmentY>(AlignmentYModes::Top);
    }

    // Third text is left aligned on bottom
    {
        nodeAt({0U, 1U})
            ->prop<SceneNodeTextProperties>()
            .put<AlignmentX>(AlignmentXModes::Left)
            .put<AlignmentY>(AlignmentYModes::Bottom);
    }

    // Fourth text is right aligned on bottom
    {
        nodeAt({1U, 1U})
            ->prop<SceneNodeTextProperties>()
            .put<AlignmentX>(AlignmentXModes::Right)
            .put<AlignmentY>(AlignmentYModes::Bottom);
    }
}

void TextQuad::configure(mtps::sptr<res::IFont> font,
                         const Color& color,
                         const mtps::vector2df& size)
{
    for (size_type count{0}; count < 4U; ++count)
    {
        auto node(nodeAt({count % 2U, count / 2U}));
        node->prop<SceneNodeTextProperties>()
            .put<Font>(font)
            .put<TextColor>(color)
            .put<AlignmentSize>(size);
    }
}

}  // namespace haf::scene::nodes
