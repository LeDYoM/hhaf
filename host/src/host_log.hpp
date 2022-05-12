#ifndef HAF_HOST_HOST_LOG_INCLUDE_HPP
#define HAF_HOST_HOST_LOG_INCLUDE_HPP

#include <hlog/include/hlog.hpp>

namespace haf
{
static constexpr char const HostLogMessage[] = "Host:";

struct HostLogOptions : logger::DefaultMessageLogOptions<HostLogMessage>
{};
using HostLogDisplayer = MessageDisplayLog<HostLogOptions>;
}  // namespace haf

#endif
