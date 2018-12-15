#pragma once

#ifndef LIB_BACKEND_SFMLB_REDNERWINDOW_INCLUDE_HPP
#define LIB_BACKEND_SFMLB_REDNERWINDOW_INCLUDE_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <lib/scene/vertexarray.hpp>
#include <lib/include/backend/iwindow.hpp>
#include <lib/include/backend/iinputdriver.hpp>
#include <lib/include/backend/irendertarget.hpp>
#include <lib/include/windowcreationparams.hpp>

#include "inputdriver.hpp"

namespace lib::backend::sfmlb
{
    class RenderTarget : public IRenderTarget, public sf::RenderTarget
    {
        void draw(const scene::Vertex *vertices, const u32 nVertex, const scene::PrimitiveType pType, const f32 *transform, const ITexture *texture) override;
        void setViewPort(const Rectf32 &nviewport) override;
        Rectf32 viewPort() const override;
        void setViewRect(const Rectf32 &nviewRect) override;
        Rectf32 viewRect() const override;
        void clear() override;
    };

    class RenderWindow : public IWindow, public RenderTarget, public sf::Window
    {
    public:

        RenderWindow();
        virtual ~RenderWindow();

        bool createWindow(const WindowCreationParams &wcp) override;
        sf::Vector2u getSize() const;

        bool activate(bool active = true) override { return sf::Window::setActive(active); }

        // Not necessary, but the headers of sf::RenderTarget in Linux, contain this definition
        bool setActive(bool active = true) { return IWindow::activate(active); }

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
}

#endif
