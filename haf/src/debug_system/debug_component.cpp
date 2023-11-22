#include <haf/include/debug_system/debug_component.hpp>
#include <haf/include/component/component_definition.hpp>

#include "system/get_system.hpp"
#include "resources/resource_manager.hpp"
#include "scene/scene_manager.hpp"
#include <haf/include/resources/vertex_array_object.hpp>

#include <haf/include/debug_system/idebug_variables.hpp>
#include <haf/include/scene/scene_node.hpp>

using namespace haf::core;

namespace haf::debug
{

DebugComponent::DebugComponent()
{}

DebugComponent::~DebugComponent() = default;

void DebugComponent::onAttached()
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .KeyPressed().connect(
            make_function(this, &DebugComponent::onKeyPressed));
}

void DebugComponent::onKeyPressed(input::Key const&)
{
    /*
    using namespace haf::input;
    switch (key)
    {

    }
    */
}

}  // namespace haf::debug
