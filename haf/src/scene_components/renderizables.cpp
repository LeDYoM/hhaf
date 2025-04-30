#include <haf/include/scene_components/renderizables.hpp>

using namespace htps;
using namespace haf::render;

namespace haf::scene
{

void RenderizableGroupComponent::onAttached()
{
    renderizables_.setSceneNode(attachedNode());
}

void RenderizableGroupComponent::update()
{
    renderizables_.updateRenderizables(true);
}

}  // namespace haf::scene
