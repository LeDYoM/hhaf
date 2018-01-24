#pragma once

#ifndef LIB_PROPERTIES_HPP
#define LIB_PROPERTIES_HPP

#include "function.hpp"

namespace lib
{
    using callback_t = function<void()>;

    template <typename T>
    class IProperty
    {
        virtual const T &get() const noexcept = 0;
        virtual void set(const T&v) noexcept = 0;
    };

    template <typename T>
    class BasicProperty : public IProperty<T>
    {
    public:
        constexpr BasicProperty() noexcept = default;
        constexpr BasicProperty(T iv) noexcept : m_value{ std::move(iv) } {}

        constexpr const T&operator()() const noexcept { return m_value; }
        constexpr void operator=(const T&v) noexcept { set(v); }
        const T &get() const noexcept override { return m_value; }
        void set(const T&v) noexcept override { m_value = v; }

    protected:
        T m_value{};
    };

    template <typename T>
    class PropertyTrigger : public BasicProperty<T>
    {
        using BaseClass = BasicProperty<T>;
    public:
        constexpr PropertyTrigger() noexcept = default;
        constexpr PropertyTrigger(T iv) noexcept : BaseClass{ std::move(iv) }, m_callback{} {}
        constexpr PropertyTrigger(callback_t c) noexcept : BaseClass{}, m_callback{ std::move(c) } {}
        constexpr PropertyTrigger(T iv, callback_t c) noexcept : BaseClass{ std::move(iv) }, m_callback{ std::move(c) } {}

        void set(const T&v) noexcept override { BaseClass::m_value = v; update(); }

        constexpr void setCallback(callback_t c) noexcept { m_callback = std::move(c); }
        constexpr void operator=(const T&v) noexcept { set(v); }

        constexpr void update() { if (m_callback) m_callback(); }

    private:
        callback_t m_callback{};
    };

    template <typename T>
    class PropertyState : public PropertyTrigger<T>
    {
        using BaseClass = PropertyTrigger<T>;
    public:
        constexpr PropertyState() noexcept : PropertyState{T{}} {}
        constexpr PropertyState(T iv) noexcept : BaseClass{ std::move(iv), [this]() { m_hasChanged = true; } } {}

        bool hasChanged() const noexcept { return m_hasChanged; }
        bool readReset_hasChanged() const noexcept { const bool v{ m_hasChanged }; resetHasChanged(); return v; }
        constexpr void resetHasChanged() noexcept { m_hasChanged = false; }
        constexpr void setChanged() noexcept { BaseClass::update(); }

    private:
        bool m_hasChanged{ true };
    };

}

#endif
