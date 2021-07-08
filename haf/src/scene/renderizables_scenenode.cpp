#include <haf/include/scene/renderizables_scenenode.hpp>
#include "scenemanager.hpp"
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
