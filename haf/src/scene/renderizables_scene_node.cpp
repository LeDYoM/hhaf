#include <haf/include/scene/renderizables_scene_node.hpp>
#include "scene_manager.hpp"
#include "system/get_system.hpp"

using namespace htps;
using namespace haf::render;

namespace haf::scene
{

RenderizablesSceneNode::RenderizablesSceneNode(rptr<SceneNode> parent,
                                               str name) :
    BaseClass{parent, std::move(name)}, render::Renderizables{this}
{}

}  // namespace haf::scene
