#pragma once

#ifndef LIB_WINDOW_WINDOW_INCLUDE_HPP
#define LIB_WINDOW_WINDOW_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/include/appservice.hpp>
#include <lib/window/include/window_properties.hpp>

namespace lib::input
{
    class InputDriver;
}

namespace lib::sys
{
class RenderTarget;
class SystemProvider;

/**
 * @brief Class containing elements to manage a window.
 * This class system is intended to be used internally to provide
 * functionallity related to a window.
 */
class Window final : public AppService
{
public:
    /**
     * @brief Construct a new Window object
     * 
     * @param system_provider The system provider
     */
    Window(sys::SystemProvider &system_provider);

    /**
     * @brief Destroy the Window object
     * 
     */
    ~Window() override;

    /**
     * @brief Creates (or tryes to create) an operating system window
     * 
     * @param window_properties Desired properties for the window
     * @return true If window creation was successful
     * @return false Failed trying to create the window
     */
    bool create(mtps::uptr<win::WindowProperties> window_properties);

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
    void onCreate();
    void onDestroy();

    mtps::sptr<RenderTarget> renderTarget();
    const mtps::sptr<RenderTarget> renderTarget() const;

    mtps::sptr<input::InputDriver> inputDriver();
    const mtps::sptr<input::InputDriver> inputDriver() const;

private:
    struct WindowPrivate;
    mtps::uptr<WindowPrivate> priv_;
};
} // namespace lib::sys

#endif
