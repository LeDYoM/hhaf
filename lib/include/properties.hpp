#pragma once

#ifndef LIB_PROPERTIES_INCLUDE_HPP
#define LIB_PROPERTIES_INCLUDE_HPP

#include <mtypes/include/properties.hpp>
#include <mtypes/include/str.hpp>

#include <lib/scene/color.hpp>

namespace lib
{
    template <typename Tag, typename T>
    class strong_typedef
    {
    public:
        strong_typedef() noexcept(std::is_nothrow_default_constructible_v<T>)
            : value_{} { }

        explicit constexpr strong_typedef(const T& value) : value_{value} { }

        explicit strong_typedef(T&& value)
        noexcept(/*std::is_nothrow_move_constructible_t<T>*/true)
            : value_{std::move(value)} { }

        template <typename... Args>
        explicit constexpr strong_typedef(Args&&... args)
            : value_{std::forward<Args>(args)...} { }

        explicit operator T&() noexcept { return value_; }
        explicit operator const T&() const noexcept {return value_; }

        const T& operator()() const noexcept { return value_; }

        friend void swap(strong_typedef& a, strong_typedef& b) noexcept
        {
            using std::swap;
            swap(static_cast<T&>(a), static_cast<T&>(b));
        }

    private:
        T value_;
    };

    struct TextTag;
    using Text_t = strong_typedef<TextTag, str>;
}

namespace lib
{
    template <typename T>
    class DoubleBufferedData
    {
        explicit constexpr DoubleBufferedData() noexcept
            : value_{}, next_value_ { }

        explicit constexpr DoubleBufferedData(const T& value) noexcept
        : value_{value} next_value_{value} { }

        explicit constexpr DoubleBufferedData(T&& value) noexcept
            : value_{std::move(value)}, next_value_{value_} { }

        template <typename... Args>
        explicit constexpr DoubleBufferedData(Args&&... args) noexcept
            : value_{std::forward<Args>(args)...}, next_value_{value_} { }

        constexpr const T& get() const noexcept { return value_; }
        constexpr const T& operator()() const noexcept { return value_; }

        constexpr void set(const T&other) const noexcept
        {
            value = other;
            has_changed_ = true;
        }

        constexpr void set(T&&other) const noexcept
        {
            std::swap(value_, other.value_);
            has_changed_ = true;
        }

        friend void swap(DoubleBufferedData& lhs, DoubleBufferedData& rhs) noexcept
        {
            std::swap(lhs.value_, rhs.value_);
            std::swap(lhs.next_value_, rhs.next_value_);
            std::swap(lhs.has_changed_, rhs.has_changed_);
        }

        DoubleBufferedData& operator=(const DoubleBufferedData&) noexcept = default;
        DoubleBufferedData& operator=(DoubleBufferedData&&) noexcept = default;

        constexpr bool has_changed() const noexcept { return has_changed_; }
        const T& update() noexcept 
        {
            next_value_ = value_;
            has_changed = false;
            return next_value;
        }

    private:
        T value_;
        T next_value;
        bool has_changed_{true};
    };
}
#endif
