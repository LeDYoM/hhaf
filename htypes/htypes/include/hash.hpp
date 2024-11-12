HTPS_PRAGMA_ONCE
#ifndef HTPS_HASH_INCLUDE_HPP
#define HTPS_HASH_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "str_literal.hpp"
#include "str_view.hpp"
#include "span.hpp"

namespace htps
{
struct Hasher
{
    template <typename T = u32, size_type N>
    static consteval T hash(char const (&s)[N]) noexcept
    {
        T hash{5381U};

        for (auto&& c : s)
        {
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }

        return hash;
    }

    template <typename T = u32, size_type N>
    static consteval T hash(str_literal<N> s) noexcept
    {
        T hash{5381U};

        for (const auto& c : s)
        {
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }

        return hash;
    }

    template <typename T = u32>
    static constexpr T hash(span<char const> const s) noexcept
    {
        T hash{5381U};


        for (auto&& c : s)
        {
            hash = ((hash << 5) + hash) + c;  // hash * 33 + c
        }

        return hash;
    }

    template <typename T = u32>
    static constexpr T hash(span<s32 const> const s) noexcept
    {
        T hash{5381U};

        for (auto&& c : s)
        {
            hash = ((hash << 5) + hash) + c;  // hash * 33 + c
        }

        return hash;
    }

    template <typename T = u32>
    static constexpr T hash(span<f32 const> const s) noexcept
    {
        static_assert(sizeof(s32) == sizeof(f32));
        return hash(*(reinterpret_cast<span<s32 const> const*>(&s)));
    }

    template <typename T = u32>
    static constexpr T hash(str_view const s) noexcept
    {
        return hash(span{s.cbegin(),s.cend()});
    }

    template <typename T = u32>
    static constexpr T hash(str const& s) noexcept
    {
        return hash(span{s.cbegin(),s.cend()});
    }
};

template <htps::str_literal Str>
struct StringHash
{
    static constexpr u32 value{Hasher::hash(Str)};
};

template <htps::str_literal Str>
inline constexpr u32 StringHash_v{StringHash<Str>::value};

}  // namespace htps

#endif
