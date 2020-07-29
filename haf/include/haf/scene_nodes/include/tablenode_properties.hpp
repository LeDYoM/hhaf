#pragma once

#ifndef HAF_SCENE_TABLENODE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_TABLENODE_PROPERTIES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/grouping_property.hpp>

namespace haf::scene
{
struct SceneNodeSize
{
    using value_type = mtps::vector2df;
};

using TableNodeProperties = mtps::PropertyGroup<SceneNodeSize>;

class TableNodePropertiesContent
{
public:
    TableNodePropertiesContent() : properties_() {}
    TableNodeProperties& tableNodeProperties() noexcept { return properties_; }
    TableNodeProperties const& tableNodeProperties() const noexcept
    {
        return properties_;
    }

private:
    TableNodeProperties properties_;
};

}  // namespace haf::scene

#endif
