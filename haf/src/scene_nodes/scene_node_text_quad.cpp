#include <haf/include/scene_nodes/scene_node_text_quad.hpp>

using namespace htps;

namespace haf::scene::nodes
{

void TextQuad::onCreated()
{
    prop<TableSize>().set({2U, 2U});
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

}  // namespace haf::scene::nodes
