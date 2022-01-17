#ifndef HAF_TYPES_GROUPING_PROPERTY_INCLUDE_HPP
#define HAF_TYPES_GROUPING_PROPERTY_INCLUDE_HPP

#include <htypes/include/grouping_property.hpp>

namespace haf::types
{
template <typename... Tag>
using PropertyGroup = htps::PropertyGroupBasic<Tag...>;
}

namespace haf
{
template <typename T>
using BasicPropertyBase = htps::BasicPropertyBase<T>;

template <typename T>
using PropertyStateBase = htps::PropertyStateBase<T>;

}  // namespace haf

#endif
