#ifndef HAF_HTYPES_INCLUDE_HPP
#define HAF_HTYPES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <htypes/include/htypes_export.hpp>

namespace haf
{
template <typename T>
using sptr = mtps::sptr<T>;

template <typename T, typename D = std::default_delete<T>>
using uptr = mtps::uptr<T, D>;

template <typename To, typename From, typename Deleter>
constexpr uptr<To> unique_pointer_cast(uptr<From, Deleter> &&p)
{ 
    return mtps::unique_pointer_cast(std::move(p));
}

template <typename T>
using wptr = mtps::wptr<T>;

template <typename T, typename... Args>
constexpr sptr<T> msptr(Args &&... args) { return mtps::msptr<T>(std::forward<Args>(args)...); }

template <typename T, typename... Args>
constexpr uptr<T> muptr(Args &&... args) { return mtps::muptr(std::forward<Args>(args)...); }

template <typename T>
constexpr wptr<T> mwptr(const sptr<T> &sp) { return mtps::mwptr<T>(sp); }

template <typename T>
using rptr = mtps::rptr<T>;

using u64 = mtps::u64;
using s64 = mtps::s64;
using u32 = mtps::u32;
using s32 = mtps::s32;
using u16 = mtps::u16;
using s16 = mtps::s16;
using u8 = mtps::u8;
using s8 = mtps::s8;
using f32 = mtps::f32;
using f64 = mtps::f64;
using size_type = mtps::size_type;
using ssize_type = mtps::ssize_type;
using fast_u64 = mtps::fast_u64;
using fast_u32 = mtps::fast_u32;
using fast_u16 = mtps::fast_u16;
using fast_u8 = mtps::fast_u8;
using fast_s64 = mtps::fast_s64;
using fast_s32 = mtps::fast_s32;
using fast_s16 = mtps::fast_s16;
using fast_s8 = mtps::fast_s8;

template <typename T, typename V>
using map = mtps::map<T,V>;

template <typename T, typename V>
using pair = mtps::pair<T,V>;
}

#endif
