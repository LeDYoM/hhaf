#include <haf/include/component/component_container_representation.hpp>
#include <haf/include/component/component.hpp>

using namespace haf::core;

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
    m_components.push_back(core::move(new_component));
}

void ComponentContainerRepresentation::push_back(
    sptr<Component> const& new_component)
{
    m_components.push_back(new_component);
}

void ComponentContainerRepresentation::resize(core::u32 const newSize)
{
    m_components.resize(newSize);
}

void ComponentContainerRepresentation::set_at_index(
    core::u32 const index,
    core::sptr<Component>&& new_component)
{
    m_components.set_at_index(index, core::move(new_component));
}

void ComponentContainerRepresentation::set_at_index(
    core::u32 const index,
    core::sptr<Component> const& new_component)
{
    m_components.set_at_index(index, new_component);
}

vector<sptr<Component>>& ComponentContainerRepresentation::components() noexcept
{
    return m_components;
}

vector<sptr<Component>> const& ComponentContainerRepresentation::components()
    const noexcept
{
    return m_components;
}

void ComponentContainerRepresentation::clear()
{
    m_components.clear();
}

}  // namespace haf::component
