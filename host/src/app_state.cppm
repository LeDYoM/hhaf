export module host:app_state;

import htypes;

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
