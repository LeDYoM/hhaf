#pragma once

#ifndef LIB_ATTACHABLE_MANAGER_INCLUDE_HPP
#define LIB_ATTACHABLE_MANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/include/attachable.hpp>

namespace lib
{
template <typename AttachableType, typename AttachedBase, bool ReturnsUnique>
class AttachableManager
{
public:
    template <bool ReturnsUnique, typename T>
    struct ReturnTypeImpl
    {
        using type = uptr<T>; 
    };

    template <typename T>
    struct ReturnTypeImpl<false, typename T>
    { 
        using type = sptr<T>;
    };

    template <typename T>
    using ReturnType = typename ReturnTypeImpl<ReturnsUnique, T>::type;

    constexpr AttachableManager(rptr<AttachableType> attachable) noexcept
        : attachable_{std::move(attachable)} {}

    virtual ~AttachableManager() {}

    template <typename T>
    ReturnType<T> create()
    {
        static_assert(
            std::is_base_of_v<scene::Attachable<AttachableType>, T>,
            "You can only use this "
            "function with types derived from AttachedBase");

        T* temp = new T();
        ReturnType<T> result = ReturnType<T>(std::move(temp));
        initialize(std::move(result.get()));
        return result;
    }

protected:
    void initialize(rptr<AttachedBase> dw)
    {
        dw->attachedNode_ = attachable_;
        dw->onAttached();
    }

    const rptr<AttachableType> attachable_;
};
} // namespace lib::scene

#endif
