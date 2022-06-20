HTPS_PRAGMA_ONCE
#ifndef HTPS_PROPERTIES_INCLUDE_HPP
#define HTPS_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties/iproperty.hpp>
#include <htypes/include/properties/basic_property.hpp>
#include <htypes/include/properties/property_state.hpp>
#include <htypes/include/properties/wrapper_property.hpp>

namespace htps
{
template <typename T,
          template <typename>
          typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr IProperty<PropertyValue>& object_property(
    T* const obj,
    PropertyType<PropertyValue>(ObjectType::*property_v))
{
    return (obj->*property_v);
}

template <typename T,
          template <typename>
          typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr IProperty<PropertyValue>& object_property(
    sptr<T> const& obj,
    PropertyType<PropertyValue>(ObjectType::*property_v))
{
    return object_property(obj.get(), property_v);
}

template <typename T,
          template <typename>
          typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr void set_property(
    T* const obj,
    PropertyType<PropertyValue>(ObjectType::*property_v),
    PropertyValue const& value)
{
    object_property(obj, property_v) = value;
}

template <typename T,
          template <typename>
          typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr void set_property(
    T* const obj,
    PropertyType<PropertyValue>(ObjectType::*property_v),
    PropertyValue&& value)
{
    object_property(obj, property_v) = htps::move(value);
}

template <typename T,
          template <typename>
          typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr void set_property(
    sptr<T> const& obj,
    PropertyType<PropertyValue>(ObjectType::*property_v),
    PropertyValue const& value)
{
    object_property(obj, property_v) = value;
}

template <typename T,
          template <typename>
          typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
constexpr void set_property(
    sptr<T> const& obj,
    PropertyType<PropertyValue>(ObjectType::*property_v),
    PropertyValue&& value)
{
    object_property(obj, property_v) = htps::move(value);
}

}  // namespace htps

#endif
