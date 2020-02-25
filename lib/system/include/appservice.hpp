#pragma once

#ifndef LIB_APP_SERVICE_INCLUDE_HPP
#define LIB_APP_SERVICE_INCLUDE_HPP

namespace lib::sys
{
class SystemProvider;
}

namespace lib
{
/**
 * @brief Class to serve as a base for all App Services.
 * An App Service is a class, instanciated by SystemProvider to give
 * functionality to the app clients.
 */
class AppService
{
protected:
    constexpr AppService(sys::SystemProvider &system_provider) noexcept
        : system_provider_{system_provider} {}

    virtual ~AppService() = default;

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
    constexpr sys::SystemProvider &systemProvider() noexcept
    {
        return system_provider_;
    }

    /**
     * @brief Get a const lvalue reference to this apps @b SystemProvider
     * 
     * @return sys::SystemProvider& Reference to the SystemProvider
     */
    constexpr sys::SystemProvider const& systemProvider() const noexcept
    {
        return system_provider_;
    }

private:
    sys::SystemProvider &system_provider_;
};
} // namespace lib

#endif
