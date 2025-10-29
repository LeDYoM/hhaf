#include <haf/include/scene_components/renderizable_group_component.hpp>

using namespace haf::core;
using namespace haf::render;

namespace haf::scene
{

void RenderizableGroupComponent::onAttached()
{
    m_renderizables.setSceneNode(attachedNode());
}

void RenderizableGroupComponent::update()
{
    //TODO: why always true?
    m_renderizables.updateRenderizables(true);
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

component::ComponentOrder::Value RenderizableGroupComponent::componentOrder()
    const noexcept
{
    return StaticComponentOrder;
}

}  // namespace haf::scene
