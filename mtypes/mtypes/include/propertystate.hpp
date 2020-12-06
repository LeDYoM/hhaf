#ifndef MTPS_PROPERTY_STATE_INCLUDE_HPP
#define MTPS_PROPERTY_STATE_INCLUDE_HPP

#include "properties.hpp"

namespace mtps
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
    using BaseClass = BasicProperty<T, Tag>;
    using type = typename BaseClass::type;
    using const_type = typename BaseClass::const_type;
    using reference = typename BaseClass::reference;
    using const_reference = typename BaseClass::const_reference;
    using pointer = typename BaseClass::pointer;
    using const_pointer = typename BaseClass::const_pointer;

public:
    constexpr PropertyState() noexcept : BaseClass{} {}
    constexpr PropertyState(T iv) noexcept : BaseClass{std::move(iv)} {}
    constexpr PropertyState(PropertyState &&) noexcept = default;
    PropertyState(const PropertyState &) = default;
    constexpr PropertyState &operator=(PropertyState &&) noexcept = default;
    constexpr PropertyState &operator=(const PropertyState &) noexcept = default;

    constexpr const T &operator=(const T &v) noexcept
    {
        set(v);
        return v;
    }

    constexpr bool hasChanged() const noexcept { return m_hasChanged; }
    constexpr void resetHasChanged() noexcept { m_hasChanged = false; }
    constexpr void setChanged() noexcept { m_hasChanged = true; }
    constexpr bool readResetHasChanged() noexcept
    {
        const bool v{m_hasChanged};
        resetHasChanged();
        return v;
    }

    inline bool set(const T &v) override
    {
        const bool is_different{BaseClass::set(v)};

        if (is_different)
        {
            setChanged();
        }
        return is_different;
    }

    inline bool set(T &&v) override
    {
        const bool is_different{BaseClass::set(std::move(v))};

        if (is_different)
        {
            setChanged();
        }
        return is_different;
    }

private:
    bool m_hasChanged{true};
};

template <typename T, typename... Args>
constexpr bool ps_hasChanged(const PropertyState<T> &arg, Args &&... args) noexcept
{
    return arg.hasChanged() || ps_hasChanged(std::forward<Args>(args)...);
}

template <typename T>
constexpr bool ps_hasChanged(const PropertyState<T> &arg) noexcept
{
    return arg.hasChanged();
}

template <typename T, typename... Args>
constexpr void ps_resetHasChanged(PropertyState<T> &arg, Args &&... args) noexcept
{
    arg.resetHasChanged();
    ps_resetHasChanged(std::forward<Args>(args)...);
}

template <typename T>
constexpr void ps_resetHasChanged(PropertyState<T> &arg) noexcept
{
    return arg.resetHasChanged();
}

template <typename T, typename... Args>
constexpr bool ps_readResetHasAnyChanged(PropertyState<T> &arg, Args &&... args) noexcept
{
    const auto result_unary{arg.readResetHasChanged()};

    if constexpr (sizeof...(Args) > 1U)
    {
        const bool result_rest{ps_readResetHasAnyChanged(std::forward<Args>(args)...)};
        return result_unary || result_rest;
    }
    else if constexpr (sizeof...(Args) > 0U)
    {
        const bool result_rest{ps_readResetHasChanged(std::forward<Args>(args)...)};
        return result_unary || result_rest;
    }
    else
    {
        return result_unary;
    }
}

template <typename T, typename... Args>
constexpr bool ps_readResetHasAllChanged(PropertyState<T> &arg, Args &&... args) noexcept
{
    const bool result_unary{arg.readResetHasChanged()};

    if constexpr (sizeof...(Args) > 1U)
    {
        const bool result_rest{ps_readResetHasAllChanged(std::forward<Args>(args)...)};
        return result_unary && result_rest;
    }
    else if constexpr (sizeof...(Args) > 0U)
    {
        const bool result_rest{ps_readResetHasChanged(std::forward<Args>(args)...)};
        return result_unary && result_rest;
    } else
    {
        return result_unary;
    }
}

template <typename T>
constexpr bool ps_readResetHasChanged(PropertyState<T> &arg) noexcept
{
    return arg.readResetHasChanged();
}
} // namespace mtps

#endif
