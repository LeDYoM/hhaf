#pragma once

#ifndef LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP__
#define LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>

namespace lib::scene
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

        class SceneNodeText : public SceneNode
        {
        public:
            SceneNodeText(SceneNode *const parent, const str &name);
            virtual ~SceneNodeText() = default;

            PropertyState<str> text;
            PropertyState<sptr<TTFont>> font;
            PropertyState<u32> characterSize;
            PropertyState<AlignmentX> alignmentX;
            PropertyState<AlignmentY> alignmentY;
            PropertyState<Rectf32> alignmentBox;

        protected:
//            void updateGeometry() override;
        private:
            void updateAlignmentX();
            void updateAlignmentY();
        };
    }
}

#endif
