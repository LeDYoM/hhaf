#pragma once

#ifndef LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP__
#define LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/include/properties.hpp>
#include <lib/scene/scenenode.hpp>

namespace lib::scene
{
    class TTFont;
    class Texture;
    namespace nodes
    {
        enum class AlignmentX : u8;
        enum class AlignmentY : u8;

        class SceneNodeText : public SceneNode
        {
            using BaseClass = SceneNode;
        public:
            SceneNodeText(SceneNode *const parent, const str &name);
            virtual ~SceneNodeText() = default;

            PropertyState<Text_t> text;
            PropertyState<sptr<TTFont>> font;
            PropertyState<u32> characterSize;
            PropertyState<AlignmentX> alignmentX;
            PropertyState<AlignmentY> alignmentY;
            PropertyState<Rectf32> alignmentBox;

        protected:
            void update() override;
        private:
            void updateAlignmentX();
            void updateAlignmentY();
        };
    }
}

#endif
