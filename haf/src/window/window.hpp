HAF_PRAGMA_ONCE
#ifndef HAF_WINDOW_WINDOW_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_INCLUDE_HPP

#include <haf/include/core/types.hpp>

#include "fps_counter.hpp"
#include "window_messages_receiver.hpp"

namespace haf::backend
{
    class IWindow;
}

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
class Window final
{
public:
    /**
     * @brief Construct a new Window object
     */
    explicit Window(core::rptr<backend::IWindow> backend_window_);

    /**
     * @brief Destroy the Window object
     */
    ~Window();

    /**
     * @brief Method to be executed before starting a cycle of the window
     * rendering
     *
     * @param time_since_start Time containing the ellapsed time since start
     * @return true The window has requested to exit
     * @return false The window did not request to exit
     */
    void preLoop(time::TimePoint const& time_since_start);

    void loop();

    /**
     * @brief Method to be executed after the cycle of a system
     */
    void postLoop();

    core::sptr<input::KeyboardData> sharedKeyboardData();
    core::sptr<input::KeyboardData const> sharedKeyboardData() const;

    bool windowWantsToExit() const noexcept;
private:
    FPSCounter fps_counter;
    WindowMessagesReceiver m_window_messages_receiver;
    core::rptr<backend::IWindow> m_backend_window{nullptr};
    core::str m_title;
};

}  // namespace haf::sys

#endif
