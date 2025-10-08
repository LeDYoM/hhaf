HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_UNORDERED_COMPONENT_GROUP_INCLUDE_HPP
#define HAF_COMPONENT_UNORDERED_COMPONENT_GROUP_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <htypes/include/types.hpp>
#include <haf/include/core/log.hpp>
#include <haf/include/component/component_container_representation.hpp>

namespace haf::component
{
/**
 * @brief class representing a group of components
 * @see Component
 */
class HAF_API UnorderedComponentGroup : private ComponentContainerRepresentation
{
    using BaseClass = ComponentContainerRepresentation;

public:
    using BaseClass::getComponent;
    using BaseClass::getComponentFromTypeIndex;
    using BaseClass::clear;
    using BaseClass::size;
    using BaseClass::operator[];

    void PushBack(core::sptr<Component>&& c);
    void PushBack(core::sptr<Component> const& c);
};

}  // namespace haf::component

#endif
