#include <lib/input/i_include/get_inputsystem.hpp>
#include <lib/input/i_include/inputsystem.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>
#include <lib/system/i_include/systemprovider.hpp>
#include <lib/system/include/isystemprovider.hpp>
#include <lib/system/i_include/get_system.hpp>

namespace lib::sys
{
const sys::InputSystem &getSystem(rptr<const scene::SceneNode> scene_node)
{
    return dynamic_cast<const sys::SystemProvider&>(scene_node->isystemProvider()).inputSystem();
}

sys::InputSystem &getSystem(rptr<scene::SceneNode> scene_node)
{
    return dynamic_cast<sys::SystemProvider&>(scene_node->isystemProvider()).inputSystem();
}

} // namespace lib::input
