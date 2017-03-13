#ifndef LIB_LOG_INCLUDE_HPP__
#define LIB_LOG_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include "config.h"
#include <lib/include/logcl.hpp>

void initLog();
void finishLog();

#ifdef USE_LOGS
	#include <sstream>

	#define EXECUTE_IN_DEBUG(x)		x
	template <typename... Args>
	constexpr inline void logDebug(Args&&... args) { logprint<LogType::Debug>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr inline void logInfo(Args&&... args) { logprint<LogType::Info>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr inline void logWarning(Args&&... args) { logprint<LogType::Warning>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr inline void logError_(Args&&... args) { logprint<LogType::Error>(std::forward<Args>(args)...); }

	#define logError(...)	logError_(__FILE__,"(",__LINE__,"): ",##__VA_ARGS__)
	#define logConstruct(...)	logDebug("Constructing ",typeid(this).name(),##__VA_ARGS__)
	#define logDestruct(...)	logDebug("Destructing  ",typeid(this).name(),##__VA_ARGS__)

	#define logConstruct_NOPARAMS	logConstruct("")
	#define logDestruct_NOPARAMS	logDestruct("")

	#define __ASSERT(cond,...) if (!(cond)) logError(##__VA_ARGS__)


#else
	#define EXECUTE_IN_DEBUG(x)	
	template <typename... Args>
	constexpr inline void logDebug(Args&&...) { }
	template <typename... Args>
	constexpr inline void logInfo(Args&&...) { }
	template <typename... Args>
	constexpr inline void logWarning(Args&&...) { }
	template <typename... Args>
	constexpr inline void logError(Args&&...) { }
	template <typename... Args>
	constexpr inline void logConstruct(Args&&...) { }
	template <typename... Args>
	constexpr inline void logDestruct(Args&&...) { }
#define logConstruct_NOPARAMS
	#define logDestruct_NOPARAMS

	template <typename T, typename ...Args>
	constexpr inline void __ASSERT(T&& cond, Args&&... args) { if (!(cond)) logError(std::forward<Args>(args)...); }
#endif
#endif
