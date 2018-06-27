#pragma once

#ifndef LIB_PROPERTIES_INCLUDE_HPP
#define LIB_PROPERTIES_INCLUDE_HPP

#include <mtypes/include/properties.hpp>
#include <mtypes/include/str.hpp>

namespace lib
{
    template <typename Tag, typename T>
    class strong_typedef
    {
    public:
        strong_typedef() noexcept(std::is_nothrow_default_constructible_v<T>)
            : value_{} { }

        explicit strong_typedef(const T& value) : value_{value} { }

        explicit strong_typedef(T&& value)
        noexcept(/*std::is_nothrow_move_constructible_t<T>*/true)
            : value_{std::move(value)} { }

        template <typename... Args>
        explicit strong_typedef(Args&&... args)
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

#endif
