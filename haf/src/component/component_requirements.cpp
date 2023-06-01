#include <haf/include/component/component_requirements.hpp>

namespace haf::component
{
bool ComponentRequirements::getOrCreateComponent(core::sptr<Component>& element,
                                                 core::str_view typeName)
{
    if (element == nullptr)
    {
        auto component{m_component_container.getOrCreateComponent(typeName)};
        element = component;
    }

    return element != nullptr;
}

}  // namespace haf::component
