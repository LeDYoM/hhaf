#ifndef HAF_BACKEND_IWINDOW_INCLUDE_HPP
#define HAF_BACKEND_IWINDOW_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
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
    virtual bool createWindow(htps::u32 const width,
                              htps::u32 const height,
                              htps::u8 const red_bpp,
                              htps::u8 const green_bpp,
                              htps::u8 const blue_bpp,
                              htps::u8 const alpha_bpp,
                              htps::u32 const num_extra_parameters,
                              htps::u32 const* const extra_parameters) = 0;

    virtual bool isAlreadyCreated() const = 0;

    virtual bool setActive(const bool activate) = 0;

    virtual bool processEvents() = 0;

    virtual void display()                                 = 0;
    virtual void setWindowTitle(htps::str const& newTitle) = 0;
    virtual void closeWindow()                             = 0;

    virtual IRenderTarget* renderTarget() = 0;
    virtual IInputDriver* inputDriver()   = 0;
    virtual htps::str settingsInfo()      = 0;
};

}  // namespace haf::backend

#endif
