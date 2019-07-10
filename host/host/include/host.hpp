#pragma once

#ifndef LIB_HOST_MAIN_INCLUDE_HPP
#define LIB_HOST_MAIN_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib
{
    class IApp;
}

namespace lib::core
{
    class Host final
    {
    public:
        Host(int argc, char *argv[]);
        ~Host();

        bool setApplication(IApp* iapp);
        int run();

    private:
        class HostPrivate;
        uptr<HostPrivate> m_private;

        bool loopStep();
        void exitProgram();
        bool update();

        enum class AppState : u8;
        AppState m_state;
        bool exit{ false };
    };
}

#endif
