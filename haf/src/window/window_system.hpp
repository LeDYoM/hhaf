HAF_PRAGMA_ONCE
#ifndef HAF_WINDOW_WINDOW_SYSTEM_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_SYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include "system/system_base.hpp"
#include "window.hpp"
#include "window_configuration.hpp"

namespace haf::sys
{
class SystemProvider;

/**
 * @brief Class containing elements to manage a window.
 * This class system is intended to be used internally to provide
 * functionallity related to a window.
 * It encapsulates an IWindow from the backend. This Window reference
 * might be already created or not.
 */
class WindowSystem final : public SystemBase
{
public:
    static constexpr char StaticTypeName[] = "WindowSystem";

    /**
     * @brief Construct a new Window system object
     * @param system_provider The system provider
     */
    WindowSystem(sys::SystemProvider& system_provider);

    /**
     * @brief Destroy the Window object
     */
    ~WindowSystem();

    /**
     * @brief Initializes the window system.
     * Also Creates (or tryes to create) an operating system window
     *
     * @param window_config_file Configuration file for the window system
     * @return true If window creation was successful
     * @return false Failed trying to create the window
     */
    bool initialize(htps::str const& window_config_file);

    /**
     * @brief Method to be executed before starting a cycle of the system
     *
     * @return true The window has requested to exit
     * @return false The window did not request to exit
     */
    bool preLoop();

    /**
     * @brief Method to be executed after the cycle of a system
     */
    void postLoop();

    htps::sptr<Window> const& window() const;

private:
    WindowConfiguration m_window_configuration;
    htps::sptr<Window> m_window;
};
}  // namespace haf::sys

#endif
