#pragma once

#ifndef LIB_WINDOW_INCLUDE_HPP
#define LIB_WINDOW_INCLUDE_HPP

#include <lib/system/appservice.hpp>

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iinputdriver.hpp>

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
}

namespace lib::core
{
    class RenderTarget;
    class Host;
    class SystemProvider;

    class Window final : public HostedAppService
    {
    public:
        Window(core::SystemProvider &system_provider, const WindowCreationParams &wcp);
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

#endif
