#ifndef HAF_SYS_SYSTEM_ACCESS_INCLUDE_HPP
#define HAF_SYS_SYSTEM_ACCESS_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::sys
{
class ISystemProvider;

/**
 * @brief This class implements basic functionality to passing around copies
 * of an @b ISystemProvider pointer. The pointer is not owned, meaning that the
 * class will not destroy (or create) it.
 */
class SystemAccess
{
public:
    /**
     * @brief Construct a new System Access object
     * @param isystem_provider Pointer to an @b ISystemProvider that will be
     * stored on this instance.
     */
    explicit SystemAccess(
        mtps::rptr<ISystemProvider> isystem_provider) noexcept;

    /**
     * @brief Destroy the System Access object
     * The destructor is virtual because this class is intended to be inherited.
     */
    virtual ~SystemAccess() noexcept;

    /**
     * @brief Get a ref-to-const version of the stored pointer.
     * @return ISystemProvider const& Reference to the object.
     */
    ISystemProvider const& isystemProvider() const noexcept;

    /**
     * @brief Get a ref-to-non-const version of the stored pointer.
     * @return ISystemProvider& Reference to the object.
     */
    ISystemProvider& isystemProvider() noexcept;

    /**
     * @brief Set the @b ISystemProvider object. It assumes it had been
     * initialized with a nullptr.
     * @return true The instance contained a nullptr and has been correctly set.
     * @return false The instance already contained a valid pointer to object or
     * you passed nullptr as parameter.
     */
    bool setSystemProvider(mtps::rptr<ISystemProvider> const);

private:
    mtps::rptr<ISystemProvider> isystem_provider_;
};
}  // namespace haf::sys

#endif
