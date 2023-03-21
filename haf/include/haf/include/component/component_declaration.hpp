HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_DECLARATION_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_DECLARATION_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_with_requirements.hpp>
#include <haf/include/component/component_base.hpp>

namespace haf
{
template <typename T>
using ComponentSPtr = haf::core::sptr<T>;
}

#endif
