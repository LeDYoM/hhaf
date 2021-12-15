#ifndef HAF_WINDOW_WINDOW_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include "system/systembase.hpp"

namespace haf::input
{
class InputDriverWrapper;
}

namespace haf::sys
{
class RenderTarget;
class SystemProvider;

/**
 * @brief Class containing elements to manage a window.
 * This class system is intended to be used internally to provide
 * functionallity related to a window.
 * It encapsulates an IWindow from the backend. This Window reference
 * might be already created or not.
 */
class Window final : public SystemBase
{
public:
    /**
     * @brief Construct a new Window object
     * @param system_provider The system provider
     */
    Window(sys::SystemProvider& system_provider);

    /**
     * @brief Destroy the Window object
     */
    ~Window();

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

    htps::sptr<RenderTarget> renderTarget();
    htps::sptr<RenderTarget const> renderTarget() const;

    htps::sptr<input::InputDriverWrapper> inputDriverWrapper();
    htps::sptr<input::InputDriverWrapper const> inputDriverWrapper() const;

private:
    struct WindowPrivate;
    htps::uptr<WindowPrivate> priv_;
};
}  // namespace haf::sys

#endif
