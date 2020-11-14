#pragma once

#ifndef HAF_HOST_MAIN_INCLUDE_HPP
#define HAF_HOST_MAIN_INCLUDE_HPP

#include <mtypes/include/types.hpp>
namespace mtps
{
class str;
}

namespace haf
{
class IApp;
}

namespace haf::host
{
struct ManagedApp;

class Host final
{
public:
    Host(int argc, char* argv[]);
    ~Host();

    bool loadApplication(mtps::str const& app_name);
    bool addApplication(mtps::rptr<IApp> iapp,
                        ManagedApp managed_app,
                        mtps::str name);
    bool unloadApplication(mtps::str const& app_name);

    int run();

private:
    class HostPrivate;
    mtps::uptr<HostPrivate> p_;

    bool loopStep();
    void exitProgram();
    bool update();

    enum class AppState : mtps::u8
    {
        NotInitialized,
        ReadyToStart,
        Executing,
        ReadyToTerminate,
        Terminated
    };

    AppState app_state_;
    bool exit{false};
};
}  // namespace haf::host

#endif
