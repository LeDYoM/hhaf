#pragma once

#ifndef LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP
#define LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <lib/include/resources/ifont.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/color.hpp>

namespace lib::scene::nodes
{
    class SceneNodeText : public SceneNode
    {
        using BaseClass = SceneNode;
    public:
        SceneNodeText(SceneNode *const parent, const str &name);
        ~SceneNodeText() override;

        PropertyState<str> text;
        PropertyState<sptr<IFont>> font;
        PropertyState<Color> textColor;
    protected:
        void update() override final;
    };
}

#endif
