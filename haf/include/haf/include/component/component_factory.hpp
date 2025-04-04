HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_FACTORY_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_FACTORY_INCLUDE_HPP

#include <haf/include/utils/object_factory.hpp>
#include <haf/include/component/component.hpp>

namespace haf::component
{
using ComponentFactory = utils::ObjectFactory<Component>;
}
#endif
