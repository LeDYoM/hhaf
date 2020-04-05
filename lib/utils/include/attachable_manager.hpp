#pragma once

#ifndef LIB_ATTACHABLE_MANAGER_INCLUDE_HPP
#define LIB_ATTACHABLE_MANAGER_INCLUDE_HPP

#include <lib/utils/include/attachable.hpp>
#include <mtypes/include/types.hpp>

namespace haf::sys
{
/**
 * @brief Utility class to define a manager/factory for a certain types of
 * classes.
 * 
 * @tparam AttachedBase Base Type of the objects to create
 */
template <typename AttachedBase>
class AttachableManager
{
public:
    using AttachableType = typename AttachedBase::AttachedNodeType;

    constexpr AttachableManager(
        mtps::rptr<AttachableType> attachable = nullptr) noexcept :
        attachable_{std::move(attachable)}
    {}

    virtual ~AttachableManager() {}

protected:
    template <typename T>
    mtps::uptr<T> create() const
    {
        // Static check that T is a valid type for this class.
        static_assert(std::is_base_of_v<sys::Attachable<AttachableType>, T>,
                      "You can only use this "
                      "function with types derived from AttachedBase");

        T* temp = new T();

        // Dynamic check that T is a valid types for this class.
        const mtps::rptr<const sys::Attachable<AttachableType>> temp2 =
            dynamic_cast<mtps::rptr<const sys::Attachable<AttachableType>>>(
                temp);
        log_assert(temp2 != nullptr, "");

        auto result = mtps::uptr<T>(std::move(temp));
        initialize(result.get());
        return result;
    }

private:
    void initialize(mtps::rptr<AttachedBase> dw) const
    {
        dw->attachedNode_ = attachable_;
        dw->onAttached();
    }

    const mtps::rptr<AttachableType> attachable_;
};
}  // namespace haf::sys

#endif
