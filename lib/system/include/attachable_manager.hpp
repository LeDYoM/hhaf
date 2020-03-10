#pragma once

#ifndef LIB_ATTACHABLE_MANAGER_INCLUDE_HPP
#define LIB_ATTACHABLE_MANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/include/attachable.hpp>

namespace lib::sys
{
template <typename AttachedBase, bool ReturnsUnique>
class AttachableManager
{
public:
    using AttachableType = typename AttachedBase::AttachedNodeType;

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

    constexpr AttachableManager(rptr<AttachableType> attachable = nullptr) noexcept
        : attachable_{std::move(attachable)} {}

    virtual ~AttachableManager() {}

protected:
    template <typename T>
    ReturnType<T> create() const
    {
        // Static check that T is a valid type for this class.
        static_assert(
            std::is_base_of_v<sys::Attachable<AttachableType>, T>,
            "You can only use this "
            "function with types derived from AttachedBase");

        T *temp = new T();

        // Dynamic check that T is a valid types for this class.
        const rptr<const sys::Attachable<AttachableType>> temp2 =
            dynamic_cast<rptr<const sys::Attachable<AttachableType>>>(temp);
        log_assert(temp2 != nullptr, "");

        ReturnType<T> result = ReturnType<T>(std::move(temp));
        initialize(result.get());
        return result;
    }

private:
    void initialize(rptr<AttachedBase> dw) const
    {
        dw->attachedNode_ = attachable_;
        dw->onAttached();
    }

    const rptr<AttachableType> attachable_;
};
} // namespace sys

#endif
