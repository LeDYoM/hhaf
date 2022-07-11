#ifndef HAF_HOST_HOST_LOG_INCLUDE_HPP
#define HAF_HOST_HOST_LOG_INCLUDE_HPP

#include <hlog/include/hlog.hpp>

namespace haf
{
static constexpr char const DebugLogMessage[] = "[Debugging] ";

struct DebugLogOptions : logger::DefaultMessageLogOptions<DebugLogMessage>
{};
using DebugLogDisplayer = MessageDisplayLog<DebugLogOptions>;

}  // namespace haf

#endif
