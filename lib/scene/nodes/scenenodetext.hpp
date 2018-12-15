#pragma once

#ifndef LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP__
#define LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/include/properties.hpp>
#include <lib/scene/scenenode.hpp>

namespace lib::scene
{
    class Font;
    namespace nodes
    {
        class SceneNodeText : public SceneNode
        {
            using BaseClass = SceneNode;
        public:
            SceneNodeText(SceneNode *const parent, const str &name);
            virtual ~SceneNodeText();

            PropertyState<Text_t> text;
            PropertyState<sptr<Font>> font;
            PropertyState<FillColor_t> textColor;
        protected:
            void update() override;
        };
    }
}

#endif
