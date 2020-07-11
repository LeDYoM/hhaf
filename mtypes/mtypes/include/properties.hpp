#pragma once

#ifndef MTPS_PROPERTIES_INCLUDE_HPP
#define MTPS_PROPERTIES_INCLUDE_HPP

namespace mtps
{
/**
 * @brief Class provides a basic interface for properties. This is the base
 * class for any Property class.
 * @tparam T Inner type of the property.
 */
template <typename T>
class IProperty
{
public:
    using type = T;
    using const_type = T const;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const *;

    /**
     * @brief Get value of the property.
     * @return const T& The content of the property.
     */
    virtual const T &get() const noexcept = 0;

    /**
     * @brief Sets the vañue of the inner type of the property.
     * 
     * @param v New value to set.
     * @return true The value has changed
     * @return false v was equal to the content, so no changes made.
     */
    virtual bool set(const T &v) = 0;
};

template <typename T>
class BasicProperty : public IProperty<T>
{
public:
    using type = typename IProperty<T>::type;
    using const_type = typename IProperty<T>::const_type;
    using reference = typename IProperty<T>::reference;
    using const_reference = typename IProperty<T>::const_reference;
    using pointer = typename IProperty<T>::pointer;
    using const_pointer = typename IProperty<T>::const_pointer;

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
    inline bool set(const T &v) override
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
    using type = BaseClass::type;
    using const_type = BaseClass::const_type;
    using reference = BaseClass::reference;
    using const_reference = BaseClass::const_reference;
    using pointer = BaseClass::pointer;
    using const_pointer = BaseClass::const_pointer;

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

    inline bool set(const T &v) override
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
