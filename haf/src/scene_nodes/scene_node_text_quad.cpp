#include <haf/include/scene_nodes/scene_node_text_quad.hpp>

using namespace htps;

namespace haf::scene::nodes
{

void TextQuad::onCreated()
{
    prop<MoveGroup>()  = true;
    prop<ScaleGroup>() = false;

    onTableNodeCreated += make_function(this, &TextQuad::onElementCreated);
    prop<TableSize>().set({2U,2U});
}

void TextQuad::update()
{
    BaseClass::update2();
}

void TextQuad::onElementCreated(htps::vector2dst index,
                                htps::sptr<SceneNodeText> const& node)
{
    if (index == vector2dst{0U, 0U})
    {
        // First text is left aligned on top
        node->prop<SceneNodeTextProperties>()
            .put<AlignmentX>(AlignmentXModes::Left)
            .put<AlignmentY>(AlignmentYModes::Top);
        ++elements_created;
    }
    else if (index == vector2dst{1U, 0U})
    {
        // Second text is right aligned op top
        node->prop<SceneNodeTextProperties>()
            .put<AlignmentX>(AlignmentXModes::Right)
            .put<AlignmentY>(AlignmentYModes::Top);
        ++elements_created;
    }
    else if (index == vector2dst{0U, 1U})
    {
        // Third text is left aligned on bottom
        node->prop<SceneNodeTextProperties>()
            .put<AlignmentX>(AlignmentXModes::Left)
            .put<AlignmentY>(AlignmentYModes::Bottom);
        ++elements_created;
    }
    else if (index == vector2dst{1U, 1U})
    {
        // Fourth text is right aligned on bottom
        node->prop<SceneNodeTextProperties>()
            .put<AlignmentX>(AlignmentXModes::Right)
            .put<AlignmentY>(AlignmentYModes::Bottom);
        ++elements_created;
    }

    if (elements_created == (2U * 2U))
    {
        allElementsCreated();
    }
}

}  // namespace haf::scene::nodes
