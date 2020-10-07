#pragma once

#ifndef MTPS_P_IMPL_POINTER_INCLUDE_HPP
#define MTPS_P_IMPL_POINTER_INCLUDE_HPP

#include "types.hpp"

namespace mtps
{
template <typename T>
class PImplPointer
{
public:
    explicit constexpr PImplPointer(rptr<T> pointer) : pointer_{pointer} {}

    PImplPointer(PImplPointer const &) = delete;
    PImplPointer& operator=(PImplPointer const&) = delete;

    constexpr PImplPointer(PImplPointer &&) noexcept = default;
    constexpr PImplPointer& operator=(PImplPointer&&) noexcept = default;

    constexpr T* operator->() noexcept
    {
        return pointer_;
    }

    constexpr T const * operator->() const noexcept
    {
        return pointer_;
    }

    constexpr T& operator*() noexcept
    {
        return *pointer_;
    }

    constexpr T const & operator*() const noexcept
    {
        return *pointer_;
    }

    ~PImplPointer() noexcept
    {
        if (pointer_ != nullptr)
        {
            delete pointer_;
            pointer_ = nullptr;
        }
    }
private:
    rptr<T> pointer_;
};

template <typename T, typename... Args>
PImplPointer<T> make_pimplp(Args&&... args)
{
    T* p = new T(std::forward<Args>(args)...);
    return PImplPointer<T>(p);
}

}  // namespace mtps

#endif
