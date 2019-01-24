#pragma once

#ifndef LIB_WINDOW_INCLUDE_HPP
#define LIB_WINDOW_INCLUDE_HPP

#include <lib/system/appservice.hpp>

#include <lib/include/backend/iwindow.hpp>
#include <lib/include/backend/iinputdriver.hpp>

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
            Window(const WindowCreationParams &wcp);
            ~Window() override;
            bool preLoop();
            void postLoop();
            virtual void onCreate();
            virtual void onDestroy();

            sptr<RenderTarget> renderTarget();
            const sptr<RenderTarget> renderTarget() const;

            backend::IInputDriver* inputDriver();
            const backend::IInputDriver* inputDriver() const;

        private:
            void create(const WindowCreationParams &wcp);
            struct WindowPrivate;
            uptr<WindowPrivate> m_wPrivate;
            str m_title;
        };
    }
}

#endif
