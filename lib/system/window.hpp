#pragma once

#ifndef LIB_WINDOW_INCLUDE_HPP
#define LIB_WINDOW_INCLUDE_HPP

#include <lib/system/appservice.hpp>

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iinputdriver.hpp>

#include <mtypes/include/types.hpp>

namespace lib::sys
{
class RenderTarget;
class SystemProvider;

class Window final : public HostedAppService
{
public:
    Window(sys::SystemProvider &system_provider);
    ~Window() override;
    bool preLoop();
    void postLoop();
    virtual void onCreate();
    virtual void onDestroy();

    sptr<RenderTarget> renderTarget();
    const sptr<RenderTarget> renderTarget() const;

    backend::IInputDriver *inputDriver();
    const backend::IInputDriver *inputDriver() const;

private:
    void create();
    struct WindowPrivate;
    uptr<WindowPrivate> priv_;
};
} // namespace lib::sys

#endif
