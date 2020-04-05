#pragma once

#ifndef LIB_HOST_MAIN_INCLUDE_HPP
#define LIB_HOST_MAIN_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace haf
{
class IApp;
}

namespace haf::sys
{
class Host final
{
public:
    Host(int argc, char *argv[]);
    ~Host();

    bool setApplication(mtps::rptr<IApp> iapp);
    int run();

private:
    class HostPrivate;
    mtps::uptr<HostPrivate> m_private;

    bool loopStep();
    void exitProgram();
    bool update();

    enum class AppState : mtps::u8;
    AppState m_state;
    bool exit{false};
};
} // namespace haf::sys

#endif
