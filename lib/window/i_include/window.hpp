#pragma once

#ifndef LIB_WINDOW_INCLUDE_HPP
#define LIB_WINDOW_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/appservice.hpp>

namespace lib::input
{
    class InputDriver;
}

namespace lib::sys
{
class RenderTarget;
class SystemProvider;

class Window final : public AppService
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

    sptr<input::InputDriver> inputDriver();
    const sptr<input::InputDriver> inputDriver() const;

private:
    void create();
    struct WindowPrivate;
    uptr<WindowPrivate> priv_;
};
} // namespace lib::sys

#endif
