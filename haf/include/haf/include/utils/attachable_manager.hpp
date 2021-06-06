#ifndef HAF_ATTACHABLE_MANAGER_INCLUDE_HPP
#define HAF_ATTACHABLE_MANAGER_INCLUDE_HPP

#include <haf/include/utils/attachable.hpp>
#include <htypes/include/types.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::utils
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

    constexpr explicit AttachableManager(
        htps::rptr<AttachableType> attachable = nullptr) noexcept :
        attachable_{std::move(attachable)}
    {}

    virtual ~AttachableManager() {}

protected:
    template <typename T>
    htps::uptr<T> create() const
    {
        // Static check that T is a valid type for this class.
        static_assert(std::is_base_of_v<Attachable<AttachableType>, T>,
                      "You can only use this "
                      "function with types derived from AttachedBase");

        T* temp = new T();

        // Dynamic check that T is a valid types for this class.
        const htps::rptr<const Attachable<AttachableType>> temp2 =
            dynamic_cast<htps::rptr<const Attachable<AttachableType>>>(temp);
        LogAsserter::log_assert(temp2 != nullptr, "");

        auto result = htps::uptr<T>(std::move(temp));
        initialize(result.get());
        return result;
    }

protected:
    htps::rptr<AttachableType> attachable() const noexcept
    {
        return attachable_;
    }

private:
    void initialize(htps::rptr<AttachedBase> dw) const
    {
        dw->attachedNode_ = attachable_;
        dw->onAttached();
    }

    const htps::rptr<AttachableType> attachable_;
};
}  // namespace haf::utils

#endif
