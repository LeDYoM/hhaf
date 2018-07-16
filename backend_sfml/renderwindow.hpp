#pragma once

#ifndef LIB_BACKEND_REDNERWINDOW_HPP__
#define LIB_BACKEND_REDNERWINDOW_HPP__

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/vertexarray.hpp>
#include <lib/include/iapp.hpp>
#include <lib/include/backend/iwindow.hpp>
#include <lib/include/backend/irendertarget.hpp>

#include <queue>

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

        // Input part
        bool arePendingKeyPresses() const override;
        bool arePendingKeyReleases() const override;

        input::Key popKeyPress() override;
        input::Key popKeyRelease() override;

    protected:
        virtual void onCreate();
        virtual void onResize();

    private:
        void keyEvent(const sf::Event &e);

        std::queue<input::Key> m_keysPressed;
        std::queue<input::Key> m_keysReleased;

    };

    class WindowBackendInfo : public IWindowProviderInfo
    {
    public:
        const str info() override;
    };
}

#endif
