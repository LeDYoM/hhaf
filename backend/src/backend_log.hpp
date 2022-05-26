#ifndef HAF_BACKEND_LOG_INCLUDE_HPP
#define HAF_BACKEND_LOG_INCLUDE_HPP

#include <hlog/include/hlog.hpp>

namespace haf
{
static constexpr char const BackendLogMessage[] = "[BackendLib] ";

struct BackendLogOptions : logger::DefaultMessageLogOptions<BackendLogMessage>
{};
using BackendLogDisplayer = MessageDisplayLog<BackendLogOptions>;
}  // namespace haf

#endif
