#pragma once

#ifndef LIB_WINDOW_INCLUDE_HPP__
#define LIB_WINDOW_INCLUDE_HPP__

#include "appservice.hpp"

#include <lib/include/backend/iwindow.hpp>

#include <lib/include/key.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

namespace lib
{
    struct WindowCreationParams;
    namespace scene
    {
        class VertexArray;
        class RenderData;
    }

    namespace core
    {
        class RenderTarget;
        class Host;
        class Window final : public AppService
        {
        public:
            Window(Host &host, const WindowCreationParams &wcp);
            ~Window() override;
            bool preLoop();
            void postLoop();
            virtual void onCreate();
            virtual void onDestroy();

            sptr<RenderTarget> renderTarget();

            bool arePendingKeyPresses() const;
            bool arePendingKeyReleases() const;

            input::Key popKeyPress();
            input::Key popKeyRelease();

        private:
            void create(const WindowCreationParams &wcp);
            struct WindowPrivate;
            uptr<WindowPrivate> m_wPrivate;
            str m_title;
        };
    }
}

#endif
