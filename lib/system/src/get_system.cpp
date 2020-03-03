#include "get_systemprovider.hpp"
#include "systemprovider.hpp"
#include "isystemprovider.hpp"
#include "get_system.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager_accessor.hpp>
#include <lib/input/i_include/inputsystem.hpp>

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

}
