#ifndef HAF_HOST_APP_STATE_INCLUDE_HPP
#define HAF_HOST_APP_STATE_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::host
{
enum class AppState : htps::u8
{
    NotInitialized,
    ReadyToStart,
    Executing,
    ReadyToTerminate,
    Terminated
};

}  // namespace haf::host

#endif
