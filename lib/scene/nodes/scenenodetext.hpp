#pragma once

#ifndef LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP
#define LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <lib/resources_interface/include/ifont.hpp>
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

    PropertyState<str> text;
    PropertyState<sptr<IFont>> font;
    PropertyState<Color> textColor;
    PropertyState<AlignmentX> alignmentX;
    PropertyState<AlignmentY> alignmentY;
    PropertyState<vector2df> alignmentSize;

protected:
    void update() override final;

private:
    void updateAlignmentX(const f32 textSizeX);
    void updateAlignmentY(const f32 textSizeY);
};
} // namespace lib::scene::nodes

#endif
