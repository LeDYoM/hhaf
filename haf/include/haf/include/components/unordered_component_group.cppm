module;

#include <haf/include/haf_export.hpp>

export module haf:components:unordered_component_group;
import :core;
import :component_container_representation;

namespace haf::component
{
/**
 * @brief class representing a group of components
 * @see Component
 */
class HAF_API UnorderedComponentGroup : public ComponentContainerRepresentation
{
    using BaseClass = ComponentContainerRepresentation;

public:
    using BaseClass::clear;
    using BaseClass::getComponent;
    using BaseClass::getComponentFromTypeIndex;
    using BaseClass::size;
    using BaseClass::operator[];

    void PushBack(sptr<Component>&& c) { BaseClass::push_back(core::move(c)); }

    void PushBack(sptr<Component> const& c) { BaseClass::push_back(c); }
};

}  // namespace haf::component
