#pragma once

#ifndef LIB_SCENE_SCENENODE_TEXT_INCLUDE_HPP__
#define LIB_SCENE_SCENENODE_TEXT_INCLUDE_HPP__

#include <lib/scene/scenenode.hpp>

#include <mtypes/include/properties.hpp>
#include <mtypes/include/str.hpp>

namespace lib::scene::nodes
{
    class SceneNodeText
    {
        using BaseClass = SceneNode;
    public:
        SceneNodeText(SceneNode *parent, str name);//, sptr<TTFont> font, const u32 characterSize, const Color &color, const Rectf32 &box);
        virtual ~SceneNodeText();

        PropertyTrigger<str> text;

        void update() override;
    };
}

#endif
