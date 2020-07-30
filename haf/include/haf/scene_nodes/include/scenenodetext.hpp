#pragma once

#ifndef HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/grouping_property.hpp>
#include <haf/resources/include/ifont.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/color.hpp>

namespace haf::scene::nodes
{

enum class AlignmentXModes : mtps::u8
{
    Left = 0,
    Center,
    Right
};

enum class AlignmentYModes : mtps::u8
{
    Top = 0,
    Middle,
    Bottom
};

struct Text
{
    using value_type = mtps::str;
};

struct Font
{
    using value_type = mtps::sptr<res::IFont>;
};

struct TextColor
{
    using value_type = Color;
};

struct AlignmentX
{
    using value_type = AlignmentXModes;
};

struct AlignmentY
{
    using value_type = AlignmentYModes;
};

struct AlignmentSize
{
    using value_type = mtps::vector2df;
};

using SceneNodeTextProperties = mtps::PropertyGroup<Text,
                                                        Font,
                                                        TextColor,
                                                        AlignmentX,
                                                        AlignmentY,
                                                        AlignmentSize>;
class SceneNodeTextPropertiesContent
{
public:
    explicit SceneNodeTextPropertiesContent() : properties_() {}
    SceneNodeTextProperties& sceneNodeTextProperties() noexcept
    {
        return properties_;
    }
    SceneNodeTextProperties const& sceneNodeTextProperties()
        const noexcept
    {
        return properties_;
    }

private:
    SceneNodeTextProperties properties_;
};

class SceneNodeText : public SceneNode, public SceneNodeTextPropertiesContent
{
    using BaseClass = SceneNode;

public:
    using SceneNode::SceneNode;
    ~SceneNodeText() override;

protected:
    void update() override final;

private:
    void updateAlignmentX(const mtps::f32 textSizeX);
    void updateAlignmentY(const mtps::f32 textSizeY);
};
}  // namespace haf::scene::nodes

#endif
