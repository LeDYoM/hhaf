#pragma once

#ifndef LIB_SCENE_TEXTQUAD_INCLUDE_HPP
#define LIB_SCENE_TEXTQUAD_INCLUDE_HPP

#include <lib/scene_nodes/include/tablenode.hpp>
#include <lib/scene_nodes/include/scenenodetext.hpp>

namespace haf::scene::nodes
{
class TextQuad : public TableNode<SceneNodeText>
{
public:
    using BaseClass = TableNode<SceneNodeText>;
    TextQuad(SceneNode *parent, mtps::str name,
             mtps::sptr<IFont> font, const Color &color, const mtps::vector2df &size);
    virtual ~TextQuad();

    inline mtps::sptr<SceneNodeText> text(mtps::vector2dst index) const noexcept
    {
        return nodeAt(std::move(index));
    }
};
} // namespace haf::scene::nodes

#endif
