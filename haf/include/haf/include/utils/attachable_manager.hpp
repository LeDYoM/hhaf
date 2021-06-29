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
        htps::rptr<AttachableType> attachable) noexcept :
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

        auto result{htps::muptr<T>()};
        initialize(*result);
        return result;
    }

private:
    void initialize(AttachedBase& dw) const
    {
        dw.attachedNode_ = attachable_;
        dw.onAttached();
    }

    const htps::rptr<AttachableType> attachable_;
};
}  // namespace haf::utils

#endif
