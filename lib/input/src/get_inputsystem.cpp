#include <lib/input/i_include/get_inputsystem.hpp>
#include <lib/input/i_include/inputsystem.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>
#include <lib/system/i_include/systemprovider.hpp>
#include <lib/system/include/isystemprovider.hpp>
#include <lib/system/i_include/get_system.hpp>
#include <lib/input/i_include/inputsystem.hpp>
#include <lib/system/i_include/get_systemprovider.hpp>

namespace lib::sys
{
template <>
const sys::InputSystem &getSystem<InputSystem>(rptr<const scene::SceneManagerAccessor> scene_manager_accessor)
{
    return getSystemProvider(scene_manager_accessor->isystemProvider()).inputSystem();
}

template <>
sys::InputSystem &getSystem<InputSystem>(rptr<scene::SceneManagerAccessor> scene_manager_accessor)
{
    return getSystemProvider(scene_manager_accessor->isystemProvider()).inputSystem();
}

template <>
const sys::InputSystem &getSystem<InputSystem>(rptr<const scene::SceneNode> scene_node)
{
    return getSystem<sys::InputSystem>(static_cast<rptr<const scene::SceneManagerAccessor>>(scene_node));
}

template <>
sys::InputSystem &getSystem<InputSystem>(rptr<scene::SceneNode> scene_node)
{
    return getSystem<sys::InputSystem>(static_cast<rptr<scene::SceneManagerAccessor>>(scene_node));
}

} // namespace lib::input
