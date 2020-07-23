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
            return GroupablePropertyImpl<
                FirstTag>::template get_property_reference<Tag_>();
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
            return GroupablePropertyImpl<
                FirstTag>::template get_property_reference<Tag_>();
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

    template <typename Tag_>
    bool set(typename Tag_::value_type&& value) noexcept
    {
        return Base::template get_property_reference<Tag_>().set(
            std::move(value));
    }

    template <typename Tag_>
    PropertyGroup& put(typename Tag_::value_type const& value) noexcept
    {
        (void)Base::template get_property_reference<Tag_>().set(value);
        return *this;
    }

    template <typename Tag_>
    PropertyGroup& put(typename Tag_::value_type&& value) noexcept
    {
        (void)Base::template get_property_reference<Tag_>().set(
            std::move(value));
        return *this;
    }

    template <typename Tag_>
    bool hasChanged() const noexcept
    {
        return Base::template get_property_reference<Tag_>().hasChanged();
    }

    template <typename Tag_>
    typename Tag_::value_type readResethasChanged() noexcept
    {
        return Base::template get_property_reference<Tag_>()
            .readResethasChanged();
    }
};

template <typename TagFirst, typename... Tag>
bool anyHasChanged(PropertyGroupImpl<TagFirst, Tag...> const& pg) noexcept
{
    bool any_has_changed =
        pg.template get_property_reference<TagFirst>().hasChanged();
    if constexpr (sizeof...(Tag) > 0)
    {
        any_has_changed |=
            anyHasChanged(static_cast<PropertyGroupImpl<Tag...>>(pg));
    }
    return any_has_changed;
}

template <typename TagFirst, typename... Tag>
bool allHaveChanged_(PropertyGroupImpl<TagFirst, Tag...> const& pg) noexcept
{
    bool any_has_changed =
        pg.template get_property_reference<TagFirst>().hasChanged();
    if constexpr (sizeof...(Tag) > 0U)
    {
        any_has_changed |=
            allHaveChanged_(static_cast<PropertyGroupImpl<Tag...>>(pg));
    }
    return any_has_changed;
}

template <typename... Tag>
bool allHaveChanged(PropertyGroup<Tag...> const& pg) noexcept
{
    return allHaveChanged_(static_cast<PropertyGroupImpl<Tag...>>(pg));
}

template <typename TagFirst, typename... Tag>
void resetHasChanged(PropertyGroupImpl<TagFirst, Tag...> const& pg) noexcept
{
    pg.template get_property_reference<TagFirst>().resetHasChanged();
    if constexpr (sizeof...(Tag) > 0U)
    {
        resetHasChanged(static_cast<PropertyGroupImpl<Tag...>>(pg));
    }
}

}  // namespace mtps

#endif
