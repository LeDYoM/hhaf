HTPS_PRAGMA_ONCE
#ifndef HAF_WINDOW_WINDOW_LOG_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_LOG_INCLUDE_HPP

#include <hlog/include/hlog.hpp>

namespace haf
{
static constexpr char const WindowLogMessage[] = "[Window] ";

struct WindowLogOptions : logger::DefaultMessageLogOptions<WindowLogMessage>
{};
using WindowLogDisplayer = MessageDisplayLog<WindowLogOptions>;
}  // namespace haf

#endif
