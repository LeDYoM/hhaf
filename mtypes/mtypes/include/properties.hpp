#pragma once

#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "function.hpp"

namespace lib
{
/// This class provides a basic interface for all Properties of
/// the system.
template <typename T>
class IProperty
{
public:
    /// Get value of the property.
    /// @return The content of the property.
    virtual const T &get() const noexcept = 0;
    virtual bool set(const T &v) noexcept = 0;
};

template <typename T>
class BasicProperty : public IProperty<T>
{
public:
    constexpr BasicProperty() noexcept = default;
    constexpr BasicProperty(BasicProperty &&) noexcept = default;
    constexpr BasicProperty(const BasicProperty &) noexcept = default;
    constexpr BasicProperty &operator=(BasicProperty &&) noexcept = default;
    constexpr BasicProperty &operator=(const BasicProperty &) noexcept = default;

    constexpr BasicProperty(T &&iv) noexcept : m_value{std::move(iv)} {}
    constexpr BasicProperty(const T &iv) noexcept : m_value{iv} {}

    constexpr const T &operator()() const noexcept { return m_value; }
    constexpr const T &operator=(const T &v) noexcept
    {
        set(v);
        return v;
    }
    inline const T &get() const noexcept override final { return m_value; }
    inline bool set(const T &v) noexcept override
    {
        if (!(m_value == v))
        {
            m_value = v;
            return true;
        }
        return false;
    }

protected:
    T m_value{};
};

template <typename T>
class PropertyState final : public BasicProperty<T>
{
    using BaseClass = BasicProperty<T>;

public:
    constexpr PropertyState() noexcept : BaseClass{} {}
    constexpr PropertyState(T iv) noexcept : BaseClass{std::move(iv)} {}
    constexpr PropertyState(PropertyState &&) noexcept = default;
    constexpr PropertyState(const PropertyState &) noexcept = default;
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

    inline bool set(const T &v) noexcept override
    {
        const bool is_different{BaseClass::set(v)};

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
constexpr bool ps_hasChanged(const PropertyState<T> &arg, Args &&... args)
{
    return arg.hasChanged() || ps_hasChanged(std::forward<Args>(args)...);
}

template <typename T>
constexpr bool ps_hasChanged(const PropertyState<T> &arg)
{
    return arg.hasChanged();
}

template <typename T, typename... Args>
constexpr void ps_resetHasChanged(PropertyState<T> &arg, Args &&... args)
{
    arg.resetHasChanged();
    ps_resetHasChanged(std::forward<Args>(args)...);
}

template <typename T>
constexpr void ps_resetHasChanged(PropertyState<T> &arg)
{
    return arg.resetHasChanged();
}

template <typename T, typename... Args>
constexpr bool ps_readResetHasAnyChanged(PropertyState<T> &arg, Args &&... args)
{
    const bool result_unary{arg.readResetHasChanged()};

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
    return result_unary;
}

template <typename T, typename... Args>
constexpr bool ps_readResetHasAllChanged(PropertyState<T> &arg, Args &&... args)
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
    }
    return result_unary;
}

template <typename T>
constexpr bool ps_readResetHasChanged(PropertyState<T> &arg)
{
    return arg.readResetHasChanged();
}
} // namespace lib

#endif
