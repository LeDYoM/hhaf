#include <haf/include/scene_components/renderizables.hpp>

using namespace htps;
using namespace haf::render;

namespace haf::scene
{

void Renderizables::onAttached()
{
    renderizables_.setSceneNode(attachedNode());
}

void Renderizables::update()
{
    //    SceneNodeBaseClass::postRender(sceneRenderContext);
    renderizables_.updateRenderizables(true);
}

}  // namespace haf::scene
