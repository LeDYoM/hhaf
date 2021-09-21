#ifndef MTPS_GROUPING_PROPERTY_INCLUDE_HPP
#define MTPS_GROUPING_PROPERTY_INCLUDE_HPP

#include "properties.hpp"
#include "propertystate.hpp"
#include <type_traits>
#include "grouping_property_impl.hpp"

namespace htps
{
/**
 * @brief Class exporting the functionality to group some properties and their
 * most important actions on them.
 * @tparam Tag Tags referencing the properties to add in the group
 */
template <typename... Tag>
struct PropertyGroupBasic : public PropertyGroupImpl<Tag...>
{
private:
    using Base = PropertyGroupImpl<Tag...>;

public:
    PropertyGroupBasic() noexcept(noexcept(PropertyGroupImpl<Tag...>{})) =
        default;
    PropertyGroupBasic(PropertyGroupBasic const&) = delete;
    PropertyGroupBasic& operator=(PropertyGroupBasic const&) = delete;
    PropertyGroupBasic(PropertyGroupBasic&&) noexcept(
        noexcept(PropertyGroupImpl<Tag...>{
            std::move(PropertyGroupImpl<Tag...>{})})) = default;
    PropertyGroupBasic& operator=(PropertyGroupBasic&&) = default;

    PropertyGroupBasic(typename Tag::value_type const&... values) :
        Base(values...)
    {}

    template <typename Tag_>
    struct ContainsTag
    {
        static constexpr bool value = Base::template ContainsTag<Tag_>::value;
    };

    template <typename Tag_>
    static constexpr bool ContainsTag_v = ContainsTag<Tag_>::value;

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>>* = nullptr>
    typename Tag_::value_type get() const noexcept
    {
        return Base::template get_property_reference<Tag_>().get();
    }

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>>* = nullptr>
    constexpr bool set(typename Tag_::value_type const& value) noexcept
    {
        return Base::template get_property_reference<Tag_>().set(value);
    }

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>>* = nullptr>
    constexpr bool set(typename Tag_::value_type&& value) noexcept
    {
        return Base::template get_property_reference<Tag_>().set(
            std::move(value));
    }

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>>* = nullptr>
    PropertyGroupBasic& put(typename Tag_::value_type const& value) noexcept
    {
        (void)Base::template get_property_reference<Tag_>().set(value);
        return *this;
    }

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>>* = nullptr>
    PropertyGroupBasic& put(typename Tag_::value_type&& value) noexcept
    {
        (void)Base::template get_property_reference<Tag_>().set(
            std::move(value));
        return *this;
    }

    template <typename Tag_>
    std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>, bool> hasChanged()
        const noexcept
    {
        return Base::template get_property_reference<Tag_>().hasChanged();
    }

    template <typename Tag_>
    std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>>
    setChanged() noexcept
    {
        Base::template get_property_reference<Tag_>().setChanged();
    }

    template <typename Tag_>
    std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>, bool>
    readResetHasChanged() noexcept
    {
        return Base::template get_property_reference<Tag_>()
            .readResetHasChanged();
    }

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>>* = nullptr>
    auto& prop() noexcept
    {
        return Base::template get_property_reference<Tag_>();
    }

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupBasic::ContainsTag_v<Tag_>>* = nullptr>
    auto const& prop() const noexcept
    {
        return Base::template get_property_reference<Tag_>();
    }

    template <typename P>
    std::enable_if_t<std::is_same_v<P, PropertyGroupBasic>, PropertyGroupBasic&>
    prop() noexcept
    {
        return *this;
    }

    template <typename P>
    std::enable_if_t<std::is_same_v<P, PropertyGroupBasic>,
                     PropertyGroupBasic const&>
    prop() const noexcept
    {
        return *this;
    }
};

template <typename T1, typename T2>
class PropertyGroupMixin : public T1, public T2
{
public:
    using T1::prop;
    using T2::prop;
    using T1::put;
    using T2::put;
};

namespace detail
{
template <typename TagFirst, typename... Tag>
bool anyHasChanged_(PropertyGroupImpl<TagFirst, Tag...> const& pg) noexcept
{
    bool any_has_changed =
        pg.template get_property_reference<TagFirst>().hasChanged();
    if constexpr (sizeof...(Tag) > 0U)
    {
        any_has_changed |=
            anyHasChanged_(static_cast<PropertyGroupImpl<Tag...>>(pg));
    }
    return any_has_changed;
}

template <typename TagFirst, typename... Tag>
bool allHaveChanged_(PropertyGroupImpl<TagFirst, Tag...> const& pg) noexcept
{
    bool all_have_changed =
        pg.template get_property_reference<TagFirst>().hasChanged();
    if constexpr (sizeof...(Tag) > 0U)
    {
        all_have_changed &=
            allHaveChanged_(static_cast<PropertyGroupImpl<Tag...>>(pg));
    }
    return all_have_changed;
}

template <typename TagFirst, typename... Tag>
void resetHasChanged_(PropertyGroupImpl<TagFirst, Tag...>& pg) noexcept
{
    pg.template get_property_reference<TagFirst>().resetHasChanged();
    if constexpr (sizeof...(Tag) > 0U)
    {
        resetHasChanged_(static_cast<PropertyGroupImpl<Tag...>&>(pg));
    }
}

}  // namespace detail

template <typename... Tag>
bool anyHasChanged(PropertyGroupBasic<Tag...> const& pg) noexcept
{
    return detail::anyHasChanged_(static_cast<PropertyGroupImpl<Tag...>>(pg));
}

template <typename... Tag>
bool allHaveChanged(PropertyGroupBasic<Tag...> const& pg) noexcept
{
    return detail::allHaveChanged_(static_cast<PropertyGroupImpl<Tag...>>(pg));
}

template <typename... Tag>
void resetHasChanged(PropertyGroupBasic<Tag...>& pg) noexcept
{
    detail::resetHasChanged_(static_cast<PropertyGroupImpl<Tag...>&>(pg));
}

template <typename... Tag>
bool readResetAnyHasChanged(PropertyGroupBasic<Tag...>& pg) noexcept
{
    bool const any_changed{anyHasChanged(pg)};
    resetHasChanged(pg);
    return any_changed;
}

template <typename... Tag>
bool readResetAllHaveChanged(PropertyGroupBasic<Tag...>& pg) noexcept
{
    bool const all_changed{allHaveChanged(pg)};
    resetHasChanged(pg);
    return all_changed;
}

}  // namespace htps

#endif
