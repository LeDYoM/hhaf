#ifndef LIB_LOG_CLIENT_INCLUDE_HPP__
#define LIB_LOG_CLIENT_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/compconfig.hpp>

enum class LogType
{
	Debug,
	Info,
	Warning,
	Error,
};

#include <sstream>

lib::write_stream &log_stream() noexcept;

void print_impl();

template<typename T, typename ...Args>
constexpr void print_impl(T&& value, Args&&... args)
{
	log_stream() << value;
	print_impl(std::forward<Args>(args)...);
}

template<LogType log_type, typename ...Args>
constexpr void logprint(Args&&...args)
{
	switch (log_type)
	{
	case LogType::Debug:
		log_stream() << "<DEBUG> :";
		break;
	case LogType::Info:
		log_stream() << "<INFO> :";
		break;
	case LogType::Warning:
		log_stream() << "<WARNING> :";
		break;
	case LogType::Error:
		log_stream() << "<ERROR> :";
		break;
	default:
		log_stream() << "<UNKNOWN> :";
		break;
	}
	print_impl(std::forward<Args>(args)...);
}

#ifdef CLIENT_USE_LOGS

#define CLIENT_EXECUTE_IN_DEBUG(x)		x
	template <typename... Args>
	constexpr void logClDebug(Args&&... args) { logprint<LogType::Debug>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr void logClInfo(Args&&... args) { logprint<LogType::Info>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr void logClWarning(Args&&... args) { logprint<LogType::Warning>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr void logClError_(Args&&... args) { logprint<LogType::Error>(std::forward<Args>(args)...); }

#define logClError(...)	logClError_(__FILE__,"(",__LINE__,"): ",##__VA_ARGS__)
#define logClConstruct(...)	logClDebug("Constructing ",typeid(this).name(),##__VA_ARGS__)
#define logClDestruct(...) logClDebug("Destructing  ",typeid(this).name(),##__VA_ARGS__)

#define logClConstruct_NOPARAMS	logClConstruct("")
#define logClDestruct_NOPARAMS	logClDestruct("")

template <typename T, typename ...Args>
constexpr void CLIENT_ASSERT(T&& cond, Args&&... args) { if (!(cond)) logClError(std::forward<Args>(args)...); }


#else
	#define EXECUTE_IN_DEBUG(x)	
	template <typename... Args>
	constexpr void logClDebug(Args&&...) { }
	template <typename... Args>
	constexpr void logClInfo(Args&&...) { }
	template <typename... Args>
	constexpr void logClWarning(Args&&...) { }
	template <typename... Args>
	constexpr void logClError(Args&&...) { }
	template <typename... Args>
	constexpr void logClConstruct(Args&&...) { }
	template <typename... Args>
	constexpr void logClDestruct(Args&&...) { }
	#define logConstruct_NOPARAMS
	#define logDestruct_NOPARAMS

	template <typename T, typename ...Args>
	constexpr void CLIENT_ASSERT(T&& cond, Args&&... args) { if (!(cond)) logClError(std::forward<Args>(args)...); }
#endif
#endif
