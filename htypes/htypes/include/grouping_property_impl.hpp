#ifndef HTPS_GROUPING_PROPERTY_IMPL_INCLUDE_HPP
#define HTPS_GROUPING_PROPERTY_IMPLINCLUDE_HPP

#include "properties.hpp"
#include "propertystate.hpp"
#include <type_traits>

namespace htps
{
/**
 * @brief Alias to encapsulate a @b PropertyState given a Tag
 *
 * @tparam Tag Type encapsulated in the PropertyState.
 * This Tag should export a value_type with the tyè contained
 * in this Tag
 */
// template <typename Tag>
// using GroupableProperty = PropertyState<typename Tag::value_type, Tag>;

template <typename Tag, typename = void>
struct PropertyTypeSelector
{
    using type = PropertyState<typename Tag::value_type, Tag>;
};
/*
template <typename Tag>
struct PropertyTypeSelector<Tag, std::void_t<typename Tag::UseBasicProperty>>
{
    using type = BasicProperty<typename Tag::value_type, Tag>;
};
*/
template <typename Tag>
struct PropertyTypeSelector<Tag, std::void_t<typename Tag::UseCustomProperty>>
{
    using type = typename Tag::UseCustomProperty::template PropertyType<Tag>;
};

template <typename Tag>
struct GroupablePropertyImpl
{
private:
    PropertyTypeSelector<Tag>::type prop_;

public:
    using GroupablePropertyOne = PropertyTypeSelector<Tag>::type;

    template <typename Tag_>
    struct ContainsTag
    {
        static constexpr bool value = std::is_same_v<Tag_, Tag>;
    };

    template <typename Tag_>
    static constexpr bool ContainsTag_v = ContainsTag<Tag_>::value;

    GroupablePropertyImpl() = default;
    GroupablePropertyImpl(typename Tag::value_type const& value) noexcept :
        prop_{value}
    {}

    GroupablePropertyImpl(typename Tag::value_type&& value) noexcept :
        prop_{std::move(value)}
    {}

    template <typename Tag_>
    std::enable_if_t<GroupablePropertyImpl::ContainsTag_v<Tag_>,
                     GroupablePropertyOne&>
    get_property_reference() noexcept
    {
        return prop_;
    }

    template <typename Tag_>
    std::enable_if_t<GroupablePropertyImpl::ContainsTag_v<Tag_>,
                     GroupablePropertyOne const&>
    cget_property_reference() const noexcept
    {
        return prop_;
    }

    template <typename Tag_>
    std::enable_if_t<GroupablePropertyImpl::ContainsTag_v<Tag_>,
                     GroupablePropertyOne const&>
    get_property_reference() const noexcept
    {
        return cget_property_reference<Tag_>();
    }
};

/**
 * @brief Base class for @b GroupableProperty It contains some common
 *
 * @tparam FirstTag First element of the group of Tag types
 * @tparam Tag... Group of tags to include inside this type. Each Tag element
 * should contain a @b Tag::value_type exporting the type it exposes.
 */
template <typename FirstTag, typename... Tag>
struct PropertyGroupImpl : public GroupablePropertyImpl<FirstTag>,
                           public PropertyGroupImpl<Tag...>
{
    using PropertyGroupImplBase = PropertyGroupImpl<Tag...>;
    PropertyGroupImpl()         = default;

    PropertyGroupImpl(typename FirstTag::value_type const& value,
                      typename Tag::value_type const&... values) :
        GroupablePropertyImpl<FirstTag>{value},
        PropertyGroupImpl<Tag...>::PropertyGroupImpl(values...)
    {}

    template <typename Tag_>
    struct ContainsTag
    {
        static constexpr bool base_value =
            PropertyGroupImplBase::template ContainsTag<Tag_>::value;
        static constexpr bool value =
            std::is_same_v<Tag_, FirstTag> || base_value;
    };

    template <typename Tag_>
    static constexpr bool ContainsTag_v =
        PropertyGroupImpl::ContainsTag<Tag_>::value;

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupImpl::ContainsTag_v<Tag_>>* = nullptr>
    auto const& get_property_reference() const noexcept
    {
        if constexpr (std::is_same_v<Tag_, FirstTag>)
        {
            return GroupablePropertyImpl<
                FirstTag>::template get_property_reference<Tag_>();
        }
        else
        {
            return PropertyGroupImpl<Tag...>::template get_property_reference<
                Tag_>();
        }
    }

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupImpl::ContainsTag_v<Tag_>>* = nullptr>
    auto const& cget_property_reference() const noexcept
    {
        return get_property_reference<Tag_>();
    }

    template <
        typename Tag_,
        std::enable_if_t<PropertyGroupImpl::ContainsTag_v<Tag_>>* = nullptr>
    auto& get_property_reference() noexcept
    {
        if constexpr (std::is_same_v<Tag_, FirstTag>)
        {
            return GroupablePropertyImpl<
                FirstTag>::template get_property_reference<Tag_>();
        }
        else
        {
            return PropertyGroupImpl<Tag...>::template get_property_reference<
                Tag_>();
        }
    }
};

/**
 * @brief Specialization for one type only
 * @tparam FirstTag Unique Tag
 */
template <typename FirstTag>
struct PropertyGroupImpl<FirstTag> : public GroupablePropertyImpl<FirstTag>
{
    template <typename Tag_>
    struct ContainsTag
    {
        static constexpr bool value =
            GroupablePropertyImpl<FirstTag>::template ContainsTag<Tag_>::value;
    };

    template <typename Tag_>
    static constexpr bool ContainsTag_v = ContainsTag<Tag_>::value;

    PropertyGroupImpl() = default;

    using GroupablePropertyImpl<FirstTag>::GroupablePropertyImpl;
    using GroupablePropertyImpl<FirstTag>::get_property_reference;
    using GroupablePropertyImpl<FirstTag>::cget_property_reference;
};

}  // namespace htps

#endif
