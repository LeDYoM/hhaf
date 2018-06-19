#pragma once

#ifndef LIB_SCENE_TEXTQUAD_HPP__
#define LIB_SCENE_TEXTQUAD_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>

namespace lib::scene::nodes
{
    class TextQuad : public SceneNode
    {
    public:
        TextQuad(SceneNode *parent, str name, sptr<TTFont> font, const u32 characterSize, const Color &color, const Rectf32 &box);
        virtual ~TextQuad();

        inline sptr<NodeText> text(const u32 index) const noexcept { return m_texts[index]; }

    private:
        Rectf32 m_box;
        sptr<NodeText> m_texts[4];
    };
}

#endif
