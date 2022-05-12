HTPS_PRAGMA_ONCE
#ifndef MTPS_TYPES_INCLUDE_HPP
#define MTPS_TYPES_INCLUDE_HPP

#include <cstdint>
#include <memory>
#include <map>
#include <type_traits>

namespace htps
{
template <class _Ty>
[[nodiscard]] constexpr _Ty&& forward(
    std::remove_reference_t<_Ty>& _Arg) noexcept
{  // forward an lvalue as either an lvalue or an rvalue
    return static_cast<_Ty&&>(_Arg);
}

template <class _Ty>
[[nodiscard]] constexpr _Ty&& forward(
    std::remove_reference_t<_Ty>&& _Arg) noexcept
{  // forward an rvalue as an rvalue
    static_assert(!std::is_lvalue_reference_v<_Ty>, "bad forward call");
    return static_cast<_Ty&&>(_Arg);
}

template <class _Ty>
[[nodiscard]] constexpr std::remove_reference_t<_Ty>&& move(_Ty&& _Arg) noexcept
{  // forward _Arg as movable
    return static_cast<std::remove_reference_t<_Ty>&&>(_Arg);
}

template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T, typename D = std::default_delete<T>>
using uptr = std::unique_ptr<T, D>;

template <typename To, typename From, typename Deleter>
uptr<To> unique_pointer_cast(uptr<From, Deleter>&& p)
{
    if (To* cast = dynamic_cast<To*>(p.get()))
    {
        uptr<To> result(cast);
        p.release();
        return result;
    }
    return uptr<To>(nullptr);
}

template <typename T>
using wptr = std::weak_ptr<T>;

template <typename T, typename... Args>
constexpr sptr<T> msptr(Args&&... args)
{
    return std::make_shared<T>(htps::forward<Args>(args)...);
}

template <typename T, typename... Args>
constexpr uptr<T> muptr(Args&&... args)
{
    return std::make_unique<T>(htps::forward<Args>(args)...);
}

template <typename T>
constexpr wptr<T> mwptr(sptr<T> const& sp)
{
    return wptr<T>(sp);
}

template <typename T>
using rptr = std::add_pointer_t<T>;

using u64        = uint64_t;
using s64        = int64_t;
using u32        = uint32_t;
using s32        = int32_t;
using u16        = uint16_t;
using s16        = int16_t;
using u8         = uint8_t;
using s8         = int8_t;
using f32        = float;
using f64        = double;
using size_type  = std::size_t;
using ssize_type = std::ptrdiff_t;
using fast_u64   = uint_fast64_t;
using fast_u32   = uint_fast32_t;
using fast_u16   = uint_fast16_t;
using fast_u8    = uint_fast8_t;
using fast_s64   = int_fast64_t;
using fast_s32   = int_fast32_t;
using fast_s16   = int_fast16_t;
using fast_s8    = int_fast8_t;

template <typename T, typename V>
using map = std::map<T, V>;

template <typename T, typename V>
using pair = std::pair<T, V>;
}  // namespace htps

#endif
