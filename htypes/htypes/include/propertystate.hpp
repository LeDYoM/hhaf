#ifndef MTPS_PROPERTY_STATE_INCLUDE_HPP
#define MTPS_PROPERTY_STATE_INCLUDE_HPP

#include "basic_property.hpp"

namespace htps
{
/**
 * @brief Class provides a property that stores the fact that has been updated.
 * It also provides methods to check and reset this updated state.
 * class for any Property class.
 * @tparam T Inner type of the property.
 */
template <typename T, typename Tag = DummyTag>
class PropertyState final : public BasicProperty<T, Tag>
{
private:
    bool has_changed_{true};
    using BaseClass = BasicProperty<T, Tag>;

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
        BaseClass{std::move(iv)}
    {}

    PropertyState(const PropertyState&) noexcept(
        std::is_nothrow_copy_constructible_v<T>) = default;
    constexpr PropertyState& operator            =(PropertyState&&) noexcept(
        std::is_nothrow_move_assignable_v<T>) = default;
    constexpr PropertyState& operator         =(PropertyState const&) noexcept(
        std::is_nothrow_copy_assignable_v<T>) = default;

    constexpr T const& operator=(T const& v) noexcept(
        std::is_nothrow_copy_assignable_v<T>)
    {
        set(v);
        return v;
    }

    constexpr T const& operator=(T&& v) noexcept(
        std::is_nothrow_move_assignable_v<T>)
    {
        set(std::move(v));
        return v;
    }

    constexpr bool hasChanged() const noexcept { return has_changed_; }
    constexpr void resetHasChanged() noexcept { has_changed_ = false; }
    constexpr void setChanged() noexcept { has_changed_ = true; }
    constexpr bool readResetHasChanged() noexcept
    {
        auto const v{has_changed_};
        resetHasChanged();
        return v;
    }

    bool set(const T& v) noexcept(noexcept(BaseClass::set(v))) override
    {
        const bool is_different{BaseClass::set(v)};

        if (is_different)
        {
            setChanged();
        }
        return is_different;
    }

    bool set(T&& v) noexcept(noexcept(BaseClass::set(std::move(v)))) override
    {
        const bool is_different{BaseClass::set(std::move(v))};

        if (is_different)
        {
            setChanged();
        }
        return is_different;
    }
};

template <typename T, typename... Args>
constexpr bool ps_hasChanged(const PropertyState<T>& arg,
                             Args&&... args) noexcept
{
    return arg.hasChanged() || ps_hasChanged(std::forward<Args>(args)...);
}

template <typename T>
constexpr bool ps_hasChanged(const PropertyState<T>& arg) noexcept
{
    return arg.hasChanged();
}

template <typename T, typename... Args>
constexpr void ps_resetHasChanged(PropertyState<T>& arg,
                                  Args&&... args) noexcept
{
    arg.resetHasChanged();
    ps_resetHasChanged(std::forward<Args>(args)...);
}

template <typename T>
constexpr void ps_resetHasChanged(PropertyState<T>& arg) noexcept
{
    return arg.resetHasChanged();
}

template <typename T, typename... Args>
constexpr bool ps_readResetHasAnyChanged(PropertyState<T>& arg,
                                         Args&&... args) noexcept
{
    const auto result_unary{arg.readResetHasChanged()};

    if constexpr (sizeof...(Args) > 1U)
    {
        const bool result_rest{
            ps_readResetHasAnyChanged(std::forward<Args>(args)...)};
        return result_unary || result_rest;
    }
    else if constexpr (sizeof...(Args) > 0U)
    {
        const bool result_rest{
            ps_readResetHasChanged(std::forward<Args>(args)...)};
        return result_unary || result_rest;
    }
    else
    {
        return result_unary;
    }
}

template <typename T, typename... Args>
constexpr bool ps_readResetHasAllChanged(PropertyState<T>& arg,
                                         Args&&... args) noexcept
{
    const bool result_unary{arg.readResetHasChanged()};

    if constexpr (sizeof...(Args) > 1U)
    {
        const bool result_rest{
            ps_readResetHasAllChanged(std::forward<Args>(args)...)};
        return result_unary && result_rest;
    }
    else if constexpr (sizeof...(Args) > 0U)
    {
        const bool result_rest{
            ps_readResetHasChanged(std::forward<Args>(args)...)};
        return result_unary && result_rest;
    }
    else
    {
        return result_unary;
    }
}

template <typename T>
constexpr bool ps_readResetHasChanged(PropertyState<T>& arg) noexcept
{
    return arg.readResetHasChanged();
}
}  // namespace htps

#endif
