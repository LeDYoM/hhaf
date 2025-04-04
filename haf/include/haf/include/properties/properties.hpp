HAF_PRAGMA_ONCE
#ifndef HAF_PROP_PROPERTIES_INCLUDE_HPP
#define HAF_PROP_PROPERTIES_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty.hpp>
#include <haf/include/properties/basic_property.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/properties/wrapper_property.hpp>

namespace haf::prop
{
template <typename T,
          template <typename> typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr IProperty<PropertyValue>& object_property(
    T* const obj,
    PropertyType<PropertyValue>(ObjectType::* property_v))
{
    return (obj->*property_v);
}

template <typename T,
          template <typename> typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr IProperty<PropertyValue>& object_property(
    core::sptr<T> const& obj,
    PropertyType<PropertyValue>(ObjectType::* property_v))
{
    return object_property(obj.get(), property_v);
}

template <typename T,
          template <typename> typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr void set_property(
    T* const obj,
    PropertyType<PropertyValue>(ObjectType::* property_v),
    PropertyValue const& value)
{
    object_property(obj, property_v) = value;
}

template <typename T,
          template <typename> typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr void set_property(
    T* const obj,
    PropertyType<PropertyValue>(ObjectType::* property_v),
    PropertyValue&& value)
{
    object_property(obj, property_v) = htps::move(value);
}

template <typename T,
          template <typename> typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr void set_property(
    core::sptr<T> const& obj,
    PropertyType<PropertyValue>(ObjectType::* property_v),
    PropertyValue const& value)
{
    object_property(obj, property_v) = value;
}

template <typename T,
          template <typename> typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr void set_property(
    core::sptr<T> const& obj,
    PropertyType<PropertyValue>(ObjectType::* property_v),
    PropertyValue&& value)
{
    object_property(obj, property_v) = core::move(value);
}
}  // namespace haf::prop

#endif
