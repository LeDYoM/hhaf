#include "debug_displayers.hpp"
#include <haf/include/component/component_container.hpp>
#include <haf/include/scene/scene_node.hpp>

using namespace haf::core;

namespace haf::debug
{
str showComponentList(rptr<scene::SceneNode> node)
{
    str data{128U};
    data += component::ComponentContainer::StaticTypeName;
    data.reserve(128U);
    data += "Node: ";
    data += node->name() + "\n\t";

    auto const numComponents{node->components()};

    for (size_type i{0U}; i < numComponents; ++i)
    {
        data += node->componentNameAt(i);
        data += ", ";
    }
    return data;
}
}  // namespace haf::debug
