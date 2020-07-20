#pragma once

#ifndef MTPS_GROUPING_PROPERTY_INCLUDE_HPP
#define MTPS_GROUPING_PROPERTY_INCLUDE_HPP

#include "properties.hpp"
#include "propertystate.hpp"

namespace mtps
{
struct Visible
{
    using value_type = bool;
};

template <typename Tag>
using GroupableProperty = PropertyState<typename Tag::value_type, Tag>;

template <typename Tag>
class GroupablePropertyImpl
{
public:
    template <typename Tag_>
    GroupableProperty<Tag_>& get_property_reference() noexcept
    {
        return prop_;
    }

    template <typename Tag_>
    GroupableProperty<Tag_> const& get_property_reference() const noexcept
    {
        return prop_;
    }

private:
    GroupableProperty<Tag> prop_;
};

template <typename FirstTag, typename... Tag>
struct PropertyGroupImpl : public GroupablePropertyImpl<FirstTag>,
                           public PropertyGroupImpl<Tag...>
{
    using Base = PropertyGroupImpl<Tag...>;

    template <typename Tag_>
    GroupableProperty<Tag_> const& get_property_reference() const noexcept
    {
        if constexpr (std::is_same_v<Tag_, FirstTag>)
        {
            return GroupablePropertyImpl<FirstTag>::template get_property_reference<Tag_>();
        }
        else
        {
            return Base::template get_property_reference<Tag_>();
        }
    }

    template <typename Tag_>
    GroupableProperty<Tag_>& get_property_reference() noexcept
    {
        if constexpr (std::is_same_v<Tag_, FirstTag>)
        {
            return GroupablePropertyImpl<FirstTag>::template get_property_reference<Tag_>();
        }
        else
        {
            return Base::template get_property_reference<Tag_>();
        }
    }

};

template <typename FirstTag>
struct PropertyGroupImpl<FirstTag> : public GroupablePropertyImpl<FirstTag>
{

    using Base = GroupablePropertyImpl<FirstTag>;
    using Base::get_property_reference;
};

template <typename... Tag>
struct PropertyGroup : public PropertyGroupImpl<Tag...>
{
    using Base = PropertyGroupImpl<Tag...>;

    template <typename Tag_>
    typename Tag_::value_type get() const noexcept
    {
        return Base::template get_property_reference<Tag_>().get();
    }

    template <typename Tag_>
    bool set(typename Tag_::value_type const& value) noexcept
    {
        return Base::template get_property_reference<Tag_>().set(value);
    }
};

}  // namespace mtps

#endif
