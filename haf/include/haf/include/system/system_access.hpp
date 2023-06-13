HAF_PRAGMA_ONCE
#ifndef HAF_SYS_SYSTEM_ACCESS_INCLUDE_HPP
#define HAF_SYS_SYSTEM_ACCESS_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::scene
{
class SceneController;
}

namespace haf::sys
{
class ISystemProvider;
class SubSystemViewer;

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
        htps::rptr<ISystemProvider> isystem_provider) noexcept;

    /**
     * @brief Destroy the System Access object
     * The destructor is virtual because this class is intended to be inherited.
     */
    virtual ~SystemAccess();

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

    SubSystemViewer subSystemViewer() const noexcept;

    htps::rptr<ISystemProvider> isystem_provider_;

private:
    friend class scene::SceneController;
};
}  // namespace haf::sys

#endif
