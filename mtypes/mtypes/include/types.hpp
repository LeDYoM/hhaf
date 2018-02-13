#pragma once

#ifndef LIB_TYPES_HPP__
#define LIB_TYPES_HPP__

#include <cstdint>
#include <memory>
#include <map>

namespace lib
{
    template <typename T>
    using sptr = std::shared_ptr<T>;

    template <typename T>
    using uptr = std::unique_ptr<T>;

    template <typename T, typename... Args>
    constexpr sptr<T> msptr(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

    template <typename T, typename... Args>
    constexpr uptr<T> muptr(Args&&... args) { return std::make_unique<T>(std::forward<Args>(args)...); }

    template <typename T>
    using wptr = std::weak_ptr<T>;

    using u64 = uint64_t;
    using s64 = int64_t;
    using u32 = uint32_t;
    using s32 = int32_t;
    using u16 = uint16_t;
    using s16 = int16_t;
    using u8 = uint8_t;
    using s8 = int8_t;
    using f32 = float;
    using f64 = double;
    using size_type = std::size_t;

    template <typename T, typename V>
    using map = std::map<T,V>;
}

#endif
