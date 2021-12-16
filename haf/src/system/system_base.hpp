#ifndef HAF_SYSTEM_SYSTEM_BASE_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_BASE_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::sys
{
class SystemProvider;
class ISystemProvider;
class SystemAccess;
class SubSystemViewer;

/**
 * @brief Class to serve as a base for all App Services.
 * An App Service is a class, instanciated by SystemProvider to give
 * functionality to the app clients.
 */
class SystemBase
{
public:
    /**
     * @brief Construct a new App Service object. This class is intended to be
     * use as a base class, so there is only one constructor and it is
     * protected.
     * @param system_provider Object to handle all systems that this class might
     * use.
     */
    explicit SystemBase(sys::ISystemProvider& system_provider) noexcept;

    /**
     * @brief Deleted copy constructor.
     */
    SystemBase(const SystemBase&) = delete;

    /**
     * @brief Deleted assignment operator.
     */
    SystemBase& operator=(const SystemBase&) = delete;

    /**
     * @brief Get a lvalue reference to this system @b SystemProvider
     *
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    SystemProvider& systemProvider() noexcept;

    /**
     * @brief Get a const lvalue reference to this system @b SystemProvider
     *
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    SystemProvider const& systemProvider() const noexcept;

    /**
     * @brief Get a lvalue reference to this system @b ISystemProvider
     *
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    ISystemProvider& isystemProvider() noexcept;

    /**
     * @brief Get a const lvalue reference to this system @b ISystemProvider
     *
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    ISystemProvider const& isystemProvider() const noexcept;

    SystemAccess systemAccess() noexcept;
    htps::rptr<SystemAccess> systemAccessPtr() noexcept;

    SubSystemViewer subSystemViewer() noexcept;
protected:
    /**
     * @brief Destroy the System Base object
     * The destructor is protected because this class is intended to be used
     * as a base class.
     */
    ~SystemBase() noexcept;

private:
    ISystemProvider& system_provider_;
    htps::uptr<SystemAccess> system_access_{nullptr};
};
}  // namespace haf::sys

#endif
