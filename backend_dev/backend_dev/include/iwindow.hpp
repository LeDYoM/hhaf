#pragma once

#ifndef HAF_BACKEND_IWINDOW_INCLUDE_HPP
#define HAF_BACKEND_IWINDOW_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include "iresourceinfo.hpp"

namespace haf::backend
{
class IRenderTarget;
class IInputDriver;

class IWindow : public IResourceInfo
{
public:
    /**
     * @brief Destroy the IWindow object
     */
    virtual ~IWindow() {}

    /**
     * @brief Create the window of the operating system.
     * This call is intended to create a window were entities can be drawn.
     * Since this could be a lot backend dependent, the interface allows some
     * optional parameters
     *
     * @param width Width of the window.
     * @param height Height of the Window.
     * @param red_bpp Number of bits for the red channel
     * @param green_bpp Number of bits for the green channel
     * @param blue_bpp Number of bits for the blue channel
     * @param alpha_bpp Number of bits for the alpha channel
     * @param num_extra_parameters Number of extra parameters
     * @param extra_parameters Pointer to an array of extra parameters
     * @return true The window is successfully created.
     * @return false Error creating the Window.
     */
    virtual bool createWindow(const mtps::u32 width,
                              const mtps::u32 height,
                              const mtps::u8 red_bpp,
                              const mtps::u8 green_bpp,
                              const mtps::u8 blue_bpp,
                              const mtps::u8 alpha_bpp,
                              const unsigned int num_extra_parameters,
                              const unsigned int* const extra_parameters) = 0;

    virtual bool isAlreadyCreated() const = 0;

    virtual bool setActive(const bool activate) = 0;

    virtual bool processEvents() = 0;

    virtual void display()                          = 0;
    virtual void setWindowTitle(mtps::str newTitle) = 0;
    virtual void closeWindow()                      = 0;

    virtual IRenderTarget* renderTarget() = 0;
    virtual IInputDriver* inputDriver()   = 0;
    virtual mtps::str settingsInfo()      = 0;
};

}  // namespace haf::backend

#endif
