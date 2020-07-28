#pragma once

#ifndef HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP

#include <mtypes/include/grouping_property.hpp>

namespace haf::scene
{
struct Visible
{
    using value_type = bool;
};

using SceneNodeProperties = mtps::PropertyGroup<Visible>;

class SceneNodePropertiesContent
{
public:
    explicit SceneNodePropertiesContent() : properties_(true) {}
    SceneNodeProperties& sceneNodeProperties() noexcept { return properties_; }
    SceneNodeProperties const& sceneNodeProperties() const noexcept
    {
        return properties_;
    }

private:
    SceneNodeProperties properties_;
};

}  // namespace haf::scene

#endif
