HAF_PRAGMA_ONCE
#ifndef HAF_PROPERTIES_IPROPERTY_STATE_INCLUDE_HPP
#define HAF_PROPERTIES_IPROPERTY_STATE_INCLUDE_HPP

namespace haf::prop
{
class IPropertyState
{
protected:
    bool has_changed_{true};
    ~IPropertyState() = default;

public:
    constexpr bool hasChanged() const noexcept { return has_changed_; }
    constexpr void resetHasChanged() noexcept { has_changed_ = false; }
    constexpr void setChanged() noexcept { has_changed_ = true; }
    constexpr bool readResetHasChanged() noexcept
    {
        bool const v{has_changed_};
        resetHasChanged();
        return v;
    }
};

template <typename... Args>
constexpr bool ps_hasChanged(IPropertyState const& arg, Args&&... args) noexcept
{
    return arg.hasChanged() || ps_hasChanged(htps::forward<Args>(args)...);
}

constexpr bool ps_hasChanged(IPropertyState const& arg) noexcept
{
    return arg.hasChanged();
}

template <typename... Args>
constexpr void ps_resetHasChanged(IPropertyState& arg, Args&&... args) noexcept
{
    arg.resetHasChanged();
    ps_resetHasChanged(htps::forward<Args>(args)...);
}

constexpr void ps_resetHasChanged(IPropertyState& arg) noexcept
{
    return arg.resetHasChanged();
}

template <typename... Args>
constexpr bool ps_readResetHasAnyChanged(IPropertyState& arg,
                                         Args&&... args) noexcept
{
    const auto result_unary{arg.readResetHasChanged()};

    if constexpr (sizeof...(Args) > 1U)
    {
        const bool result_rest{
            ps_readResetHasAnyChanged(htps::forward<Args>(args)...)};
        return result_unary || result_rest;
    }
    else if constexpr (sizeof...(Args) > 0U)
    {
        const bool result_rest{
            ps_readResetHasChanged(htps::forward<Args>(args)...)};
        return result_unary || result_rest;
    }
    else
    {
        return result_unary;
    }
}

template <typename... Args>
constexpr bool ps_readResetHasAllChanged(IPropertyState& arg,
                                         Args&&... args) noexcept
{
    bool const result_unary{arg.readResetHasChanged()};

    if constexpr (sizeof...(Args) > 1U)
    {
        bool const result_rest{
            ps_readResetHasAllChanged(htps::forward<Args>(args)...)};
        return result_unary && result_rest;
    }
    else if constexpr (sizeof...(Args) > 0U)
    {
        bool const result_rest{
            ps_readResetHasChanged(htps::forward<Args>(args)...)};
        return result_unary && result_rest;
    }
    else
    {
        return result_unary;
    }
}

constexpr bool ps_readResetHasChanged(IPropertyState& arg) noexcept
{
    return arg.readResetHasChanged();
}
/*
constexpr bool ps_readResetHasAnyChanged(IPropertyState& arg) noexcept
{
    return ps_readResetHasChanged(arg);
}
*/
}  // namespace haf::prop

#endif
