#include <lib/input/i_include/get_inputsystem.hpp>
#include <lib/input/i_include/inputsystem.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>
#include <lib/system/i_include/systemprovider.hpp>

namespace lib::input
{
const sys::InputSystem &getInputSystem(rptr<const scene::SceneNode> scene_node)
{
    return scene_node->sceneManager().systemProvider().inputSystem();
}

sys::InputSystem &getInputSystem(rptr<scene::SceneNode> scene_node)
{
    return scene_node->sceneManager().systemProvider().inputSystem();
}

} // namespace lib::input
