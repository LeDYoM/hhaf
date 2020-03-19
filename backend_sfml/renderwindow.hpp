#pragma once

#ifndef LIB_BACKEND_SFMLB_REDNERWINDOW_INCLUDE_HPP
#define LIB_BACKEND_SFMLB_REDNERWINDOW_INCLUDE_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iinputdriver.hpp>

#include "rendertarget.hpp"
#include "inputdriver.hpp"

namespace lib::backend::sfmlb
{
class RenderWindow : public IWindow, public RenderTarget, public sf::Window
{
public:
    RenderWindow();
    virtual ~RenderWindow();

    bool createWindow(const unsigned int, const unsigned int* const) override;
    sf::Vector2u getSize() const;

    bool setActive(bool active = true) override;

    IRenderTarget *renderTarget() override;

    bool processEvents() override;
    void display() override;
    void setWindowTitle(str newTitle) override;
    void closeWindow() override;

    virtual IInputDriver *inputDriver() override;

protected:
    virtual void onCreate();
    virtual void onResize();

private:
    InputDriver input_driver_;
};

class WindowBackendInfo : public IWindowProviderInfo
{
public:
    const str info() override;
};
} // namespace lib::backend::sfmlb

#endif
