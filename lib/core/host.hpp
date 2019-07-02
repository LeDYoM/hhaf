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
    class Host final : public SystemProvider
    {
    public:
        static bool createHost(int argc, char *argv[]);
        static bool destroyHost() noexcept;

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
        class HostPrivate;
        uptr<HostPrivate> m_private;

        bool loopStep();

        AppState m_state;
        bool exit{ false };
    };
}

#endif
