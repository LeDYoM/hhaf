#ifndef LIB_LOG_INCLUDE_HPP__
#define LIB_LOG_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/compconfig.hpp>
#include <lib/include/logcl.hpp>

void initLog();
void finishLog();

#ifdef USE_LOGS
	#include <sstream>

	#define EXECUTE_IN_DEBUG(x)		x
	template <typename... Args>
	constexpr void logDebug(Args&&... args) { logprint<LogType::Debug>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr void logInfo(Args&&... args) { logprint<LogType::Info>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr void logWarning(Args&&... args) { logprint<LogType::Warning>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr void logError_(Args&&... args) { logprint<LogType::Error>(std::forward<Args>(args)...); }

	#define logError(...)	logError_(__FILE__,"(",__LINE__,"): ",##__VA_ARGS__)
	#define logConstruct(...)	logDebug("Constructing ",typeid(this).name(),##__VA_ARGS__)
	#define logDestruct(...)	logDebug("Destructing  ",typeid(this).name(),##__VA_ARGS__)

	#define logConstruct_NOPARAMS	logConstruct("")
	#define logDestruct_NOPARAMS	logDestruct("")

	#define __ASSERT(cond,...) if (!(cond)) logError(##__VA_ARGS__)


#else
	#define EXECUTE_IN_DEBUG(x)	
	template <typename... Args>
	constexpr void logDebug(Args&&...) { }
	template <typename... Args>
	constexpr void logInfo(Args&&...) { }
	template <typename... Args>
	constexpr void logWarning(Args&&...) { }
	template <typename... Args>
	constexpr void logError(Args&&...) { }
	template <typename... Args>
	constexpr void logConstruct(Args&&...) { }
	template <typename... Args>
	constexpr void logDestruct(Args&&...) { }
#define logConstruct_NOPARAMS
	#define logDestruct_NOPARAMS

	template <typename T, typename ...Args>
	constexpr void __ASSERT(T&& cond, Args&&... args) { if (!(cond)) logError(std::forward<Args>(args)...); }
#endif
#endif
