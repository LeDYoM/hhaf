#pragma once

#ifndef HAF_TYPES_BASIC_TYPES_INCLUDE_HPP
#define HAF_TYPES_BASIC_TYPES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/p_impl_pointer.hpp>

namespace haf::types
{
template <typename T>
using sptr = htps::sptr<T>;

template <typename T, typename D = std::default_delete<T>>
using uptr = htps::uptr<T, D>;

template <typename To, typename From, typename Deleter>
uptr<To> unique_pointer_cast(uptr<From, Deleter>&& p)
{
    return htps::unique_pointer_cast(std::move(p));
}

template <typename T>
using wptr = htps::wptr<T>;

template <typename T, typename... Args>
constexpr sptr<T> msptr(Args&&... args)
{
    return htps::msptr<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
constexpr uptr<T> muptr(Args&&... args)
{
    return htps::muptr<T>(std::forward<Args>(args)...);
}

template <typename T>
constexpr wptr<T> mwptr(sptr<T> const& sp)
{
    return htps::wptr<T>(sp);
}

template <typename T>
using rptr = htps::rptr<T>;

using u64        = htps::u64;
using s64        = htps::s64;
using u32        = htps::u32;
using s32        = htps::s32;
using u16        = htps::u16;
using s16        = htps::s16;
using u8         = htps::u8;
using s8         = htps::s8;
using f32        = htps::f32;
using f64        = htps::f64;
using size_type  = htps::size_type;
using ssize_type = htps::ssize_type;
using fast_u64   = htps::fast_u64;
using fast_u32   = htps::fast_u32;
using fast_u16   = htps::fast_u16;
using fast_u8    = htps::fast_u8;
using fast_s64   = htps::fast_s64;
using fast_s32   = htps::fast_s32;
using fast_s16   = htps::fast_s16;
using fast_s8    = htps::fast_s8;

template <typename T, typename V>
using map = htps::map<T, V>;

template <typename T, typename V>
using pair = htps::pair<T, V>;

using str = htps::str;

template <typename T>
using PImplPointer = htps::PImplPointer<T>;

template <typename T, typename... Args>
PImplPointer<T> make_pimplp(Args&&... args)
{
    T* p = new T(std::forward<Args>(args)...);
    return PImplPointer<T>(p);
}

}  // namespace haf::types
#endif
