module;

#include <haf/include/haf_export.hpp>

export module haf:components:ordered_component_group;

import :core;
import :component_container_representation;

namespace haf::component
{
/**
 * @brief class representing a group of components
 * @see Component
 */
class HAF_API OrderedComponentGroup : public ComponentContainerRepresentation
{
    using BaseClass = ComponentContainerRepresentation;

public:
    using BaseClass::clear;
    using BaseClass::getComponent;
    using BaseClass::getComponentFromTypeIndex;
    using BaseClass::size;
    using BaseClass::operator[];

    void insertAtIndex(u32 const index, sptr<Component>&& c)
    {
        BaseClass::set_at_index(index, core::move(c));
    }

    void insertAtIndex(u32 const index, sptr<Component> const& c)
    {
        BaseClass::set_at_index(index, c);
    }
};

}  // namespace haf::component
