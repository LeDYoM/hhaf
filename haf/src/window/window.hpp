HTPS_PRAGMA_ONCE
#ifndef HAF_WINDOW_WINDOW_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

namespace haf::input
{
class InputDriverWrapper;
}

namespace haf::backend
{
    class IWindow;
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
class Window final
{
public:
    /**
     * @brief Construct a new Window object
     */
    Window(htps::rptr<backend::IWindow> backend_window_,
           htps::sptr<input::InputDriverWrapper> input_driver_wrapper_,
           htps::sptr<RenderTarget> render_target_);

    /**
     * @brief Destroy the Window object
     */
    ~Window();

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
