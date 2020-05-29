#pragma once

#ifndef HAF_SCENE_TEXTQUAD_INCLUDE_HPP
#define HAF_SCENE_TEXTQUAD_INCLUDE_HPP

#include <haf/scene_nodes/include/tablenode.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>

namespace haf::scene::nodes
{
class TextQuad : public TableNode<SceneNodeText>
{
public:
    using BaseClass = TableNode<SceneNodeText>;
    using BaseClass::BaseClass;
    ~TextQuad() override;

    void configure(mtps::sptr<IFont> font,
                   const Color& color,
                   const mtps::vector2df& size);

    inline mtps::sptr<SceneNodeText> text(mtps::vector2dst index) const noexcept
    {
        return nodeAt(std::move(index));
    }
};
}  // namespace haf::scene::nodes

#endif
