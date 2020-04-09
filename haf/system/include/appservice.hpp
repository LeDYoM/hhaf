#pragma once

#ifndef HAF_APP_SERVICE_INCLUDE_HPP
#define HAF_APP_SERVICE_INCLUDE_HPP

namespace haf::sys
{
class SystemProvider;
class ISystemProvider;
}

namespace haf
{
/**
 * @brief Class to serve as a base for all App Services.
 * An App Service is a class, instanciated by SystemProvider to give
 * functionality to the app clients.
 */
class AppService
{
protected:
    AppService(sys::SystemProvider &system_provider) noexcept;
    virtual ~AppService();

public:
    /**
     * @brief Deleted copy constructor.
     */
    AppService(const AppService &) = delete;

    /**
     * @brief Deleted assignment operator.
     */
    AppService &operator=(const AppService &) = delete;

    /**
     * @brief Get a lvalue reference to this apps @b SystemProvider
     * 
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    sys::SystemProvider &systemProvider() noexcept;

    /**
     * @brief Get a const lvalue reference to this apps @b SystemProvider
     * 
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    sys::SystemProvider const& systemProvider() const noexcept;

    /**
     * @brief Get a lvalue reference to this apps @b ISystemProvider
     * 
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    sys::ISystemProvider &isystemProvider() noexcept;

    /**
     * @brief Get a const lvalue reference to this apps @b ISystemProvider
     * 
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    sys::ISystemProvider const& isystemProvider() const noexcept;

private:
    sys::SystemProvider &system_provider_;
};
} // namespace haf

#endif
