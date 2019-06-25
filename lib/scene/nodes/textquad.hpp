#pragma once

#ifndef LIB_SCENE_TEXTQUAD_INCLUDE_HPP
#define LIB_SCENE_TEXTQUAD_INCLUDE_HPP

#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/nodes/scenenodetext.hpp>

namespace lib::scene::nodes
{
    class TextQuad : public TableNode<SceneNodeText>
    {
    public:
        using BaseClass = TableNode<SceneNodeText>;
        TextQuad(SceneNode *parent, str name,
                 sptr<IFont> font, const Color &color, const vector2df &size);
        virtual ~TextQuad();

        inline sptr<SceneNodeText> text(vector2dst index) const noexcept
        { return nodeAt(std::move(index)); }

    private:
        vector2df m_size;
    };
}

#endif
