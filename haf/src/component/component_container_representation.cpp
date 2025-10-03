#include "component_container_representation.hpp"
#include <haf/include/component/component.hpp>

namespace haf::component
{

sptr<Component> ComponentContainerRepresentation::getComponentFromTypeIndex(
    utils::type_index const& tindex) const
{
    auto iterator(m_components.find_if(
        m_components.cbegin(), m_components.cend(),
        [&tindex](sptr<Component> const& component) {
            return utils::type_index(typeid(*component)) == tindex;
        }));
    return (iterator == m_components.cend()) ? nullptr : (*iterator);
}

void ComponentContainerRepresentation::push_back(
    sptr<Component>&& new_component)
{
    
}

}  // namespace haf::component
