#pragma once

#ifndef LIB_HOST_MAIN_INCLUDE_HPP
#define LIB_HOST_MAIN_INCLUDE_HPP

#include "apploader.hpp"

#include <mtypes/include/types.hpp>

#include <lib/include/iapp.hpp>
#include <lib/include/core/ihostcontext.hpp>
#include <lib/system/systemprovider.hpp>

namespace lib::input
{
    class InputSystem;
}

namespace lib::scene
{
    class SceneManager;
}

namespace lib::core
{
    class Window;
    class ResourceManager;
    class RandomSystem;
    class HostPrivate;

    class Host final : public SystemProvider
    {
    public:
        static bool createHost(int argc, char *argv[]);
        static bool destroyHost() noexcept;

        inline static Host &host() noexcept { return *m_instance; }
        enum class AppState : u8;
        Host(int argc, char *argv[]);
        ~Host();

        bool setApplication(IApp* iapp);
        int run();
        bool update();

        void exitProgram();

        template <typename T>
        T &app() { return *(dynamic_cast<T*>(&app())); }
        IApp &app();

    private:
        friend class lib::core::HostPrivate;
        uptr<HostPrivate> m_private;

        bool loopStep();

        static Host *m_instance;

        AppState m_state;
        bool exit{ false };
    };
}

namespace lib
{
    template <typename AppType>
    inline AppType &app() {
        return core::Host::host().app<AppType>();
    }
}

#endif
