#pragma once

#ifndef HAF_BACKEND_SFMLB_REDNERWINDOW_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_REDNERWINDOW_INCLUDE_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iinputdriver.hpp>

#include "rendertarget.hpp"
#include "inputdriver.hpp"

namespace haf::backend::sfmlb
{
class RenderWindow : public IWindow, public RenderTarget, public sf::Window
{
public:
    RenderWindow();
    virtual ~RenderWindow();

    bool createWindow(
            const mtps::u32 width, const mtps::u32 height,
            const mtps::u8 red_bpp, const mtps::u8 green_bpp, const mtps::u8 blue_bpp,
            const mtps::u8 alpha_bpp,
            const unsigned int num_extra_parameters, 
            const unsigned int* const extra_parameters) override;
    sf::Vector2u getSize() const;

    bool setActive(bool active = true) override;

    IRenderTarget *renderTarget() override;

    bool processEvents() override;
    void display() override;
    void setWindowTitle(mtps::str newTitle) override;
    void closeWindow() override;

    IInputDriver *inputDriver() override;
    mtps::str info() override;

protected:
    virtual void onCreate();
    virtual void onResize();

private:
    InputDriver input_driver_;
};

} // namespace haf::backend::sfmlb

#endif
