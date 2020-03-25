#pragma once

#ifndef LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP
#define LIB_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <lib/resources/include/ifont.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/color.hpp>

namespace lib::scene::nodes
{
class SceneNodeText : public SceneNode
{
    using BaseClass = SceneNode;

public:
    SceneNodeText(SceneNode *const parent, const mtps::str&name);
    ~SceneNodeText() override;

    enum class AlignmentX : mtps::u8
    {
        Left = 0,
        Center,
        Right
    };

    enum class AlignmentY : mtps::u8
    {
        Top = 0,
        Middle,
        Bottom
    };

    mtps::PropertyState<mtps::str> text;
    mtps::PropertyState<mtps::sptr<IFont>> font;
    mtps::PropertyState<Color> textColor;
    mtps::PropertyState<AlignmentX> alignmentX;
    mtps::PropertyState<AlignmentY> alignmentY;
    mtps::PropertyState<mtps::vector2df> alignmentSize;

protected:
    void update() override final;

private:
    void updateAlignmentX(const mtps::f32 textSizeX);
    void updateAlignmentY(const mtps::f32 textSizeY);
};
} // namespace lib::scene::nodes

#endif
