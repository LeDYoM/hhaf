#pragma once

#ifndef HAF_APP_SERVICE_INCLUDE_HPP
#define HAF_APP_SERVICE_INCLUDE_HPP

namespace haf::sys
{
class SystemProvider;
class ISystemProvider;

/**
 * @brief Class to serve as a base for all App Services.
 * An App Service is a class, instanciated by SystemProvider to give
 * functionality to the app clients.
 */
class AppService
{
public:
    /**
     * @brief Construct a new App Service object. This class is intended to be
     * use as a base class, so there is only one constructor and it is
     * protected.
     * @param system_provider Object to handle all systems that this class might
     * use.
     */
    AppService(sys::ISystemProvider& system_provider) noexcept;
    virtual ~AppService();

    /**
     * @brief Deleted copy constructor.
     */
    AppService(const AppService&) = delete;

    /**
     * @brief Deleted assignment operator.
     */
    AppService& operator=(const AppService&) = delete;

    /**
     * @brief Get a lvalue reference to this apps @b SystemProvider
     *
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    SystemProvider& systemProvider() noexcept;

    /**
     * @brief Get a const lvalue reference to this apps @b SystemProvider
     *
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    SystemProvider const& systemProvider() const noexcept;

    /**
     * @brief Get a lvalue reference to this apps @b ISystemProvider
     *
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    ISystemProvider& isystemProvider() noexcept;

    /**
     * @brief Get a const lvalue reference to this apps @b ISystemProvider
     *
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    ISystemProvider const& isystemProvider() const noexcept;

private:
    ISystemProvider& system_provider_;
};
}  // namespace haf::sys

#endif
