HTPS_PRAGMA_ONCE
#ifndef HAF_PROPERTIES_PROPERTY_STATE_INCLUDE_HPP
#define HAF_PROPERTIES_PROPERTY_STATE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/properties/basic_property.hpp>
#include <haf/include/properties/iproperty_state.hpp>

namespace haf::prop
{
/**
 * @brief Class provides a property that stores the fact that has been updated.
 * It also provides methods to check and reset this updated state.
 * class for any Property class.
 * @tparam T Inner type of the property.
 */
template <typename T>
class PropertyState final : public BasicProperty<T>, public IPropertyState
{
private:
    using BaseClass = BasicProperty<T>;

public:
    using value_type      = typename BaseClass::value_type;
    using const_type      = typename BaseClass::const_type;
    using reference       = typename BaseClass::reference;
    using const_reference = typename BaseClass::const_reference;
    using pointer         = typename BaseClass::pointer;
    using const_pointer   = typename BaseClass::const_pointer;

    /**
     * @brief Default constructor.
     * Constructs a property state with the default value of the contained
     * type.
     */
    constexpr PropertyState() noexcept(std::is_default_constructible_v<T>) =
        default;

    /**
     * @brief Constructs a property from a value from the property
     */
    constexpr PropertyState(T const& iv) noexcept(
        std::is_nothrow_copy_constructible_v<T>) :
        BaseClass{iv}
    {}
    constexpr PropertyState(T&& iv) noexcept(
        std::is_nothrow_move_constructible_v<T>) :
        BaseClass{htps::move(iv)}
    {}

    PropertyState(const PropertyState&) noexcept(
        std::is_nothrow_copy_constructible_v<T>) = default;
    constexpr PropertyState& operator            =(PropertyState&&) noexcept(
        std::is_nothrow_move_assignable_v<T>) = default;
    constexpr PropertyState& operator         =(PropertyState const&) noexcept(
        std::is_nothrow_copy_assignable_v<T>) = default;

    constexpr void operator=(T const& v) noexcept(
        std::is_nothrow_copy_assignable_v<T>) override
    {
        BaseClass::operator=(v);
        setChanged();
    }

    constexpr void operator=(T&& v) noexcept(
        std::is_nothrow_move_assignable_v<T>) override
    {
        BaseClass::operator=(core::move(v));
        setChanged();
    }

    constexpr void assignIfDifferent(T const& v) noexcept(
        std::is_nothrow_copy_assignable_v<T>)
    {
        if (BaseClass::m_value != v)
        {
            *this = v;
        }
    }

    constexpr void assignIfDifferent(T&& v) noexcept(
        std::is_nothrow_move_assignable_v<T>)
    {
        if (BaseClass::m_value != core::forward<T>(v))
        {
            *this = core::move(v);
        }
    }

    constexpr T& modify() noexcept
    {
        setChanged();
        return BaseClass::m_value;
    }
};

}  // namespace haf::prop

#endif
