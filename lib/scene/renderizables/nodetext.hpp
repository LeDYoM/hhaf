#pragma once

#ifndef LIB_SCENE_RENDERIZABLES_NODETEXT_HPP__
#define LIB_SCENE_RENDERIZABLES_NODETEXT_HPP__

#include <lib/scene/renderizable.hpp>
#include <mtypes/include/types.hpp>

namespace lib
{
    namespace scene
    {
        class TTFont;
        class Texture;
        namespace nodes
        {
            enum class AlignmentX : u8
            {
                Left = 0,
                Center,
                Right
            };

            enum class AlignmentY : u8
            {
                Top = 0,
                Middle,
                Bottom
            };

            class NodeText : public Renderizable
            {
            public:
                NodeText(SceneNode *const parent, const str &name);
                virtual ~NodeText() = default;

                PropertyState<str> text;
                PropertyState<sptr<TTFont>> font;
                PropertyState<u32> characterSize;
                PropertyState<AlignmentX> alignmentX;
                PropertyState<AlignmentY> alignmentY;
                PropertyState<Rectf32> alignmentBox;

            protected:
                void updateGeometry() override;
            private:
                void updateAlignmentX();
                void updateAlignmentY();
            };
        }
    }
}

#endif
