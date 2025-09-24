#include <haf/include/scene_components/renderizable_group_component.hpp>

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

sptr<render::Renderizable> const& RenderizableGroupComponent::first()
    const noexcept
{
    LogAsserter::log_assert(!emptyRenderizables(),
                            "The Renderizables vector is empty");
    return RenderizableGroupComponent::operator[](0U);
}

str RenderizableGroupComponent::staticTypeName() const noexcept
{
    return str{RenderizableGroupComponent::StaticTypeName};
}

}  // namespace haf::scene
