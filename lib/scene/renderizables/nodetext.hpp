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

                Property<str> text;
                Property<sptr<TTFont>> font;
                Property<u32> characterSize;
                Property<AlignmentX> alignmentX;
                Property<AlignmentY> alignmentY;
                Property<Rectf32> alignmentBox;

                bool hasChanged() const {
                    return text.hasChanged() || font.hasChanged() || characterSize.hasChanged() || alignmentX.hasChanged() || alignmentY.hasChanged() || alignmentBox.hasChanged();
                }

                void resetHasChanged() {
                    text.resetHasChanged();
                    font.resetHasChanged();
                    characterSize.resetHasChanged();
                    alignmentX.resetHasChanged();
                    alignmentY.resetHasChanged();
                    alignmentBox.resetHasChanged();
                }

            protected:
                void updateGeometry();
            private:
                void updateAlignmentX();
                void updateAlignmentY();
            };
        }
    }
}

#endif
