#ifndef LIB_LOG_INCLUDE_HPP__
#define LIB_LOG_INCLUDE_HPP__

#include "compileconfig.hpp"
#include <iostream>

void initLog();
void finishLog();

#ifdef __USE_LOGS__
	#include <sstream>
	enum class LogType
	{
		Debug,
		Info,
		Warning,
		Error,
	};

	std::ostream &log_stream();

	void print_impl();

	template<typename T, typename ...Args>
	inline void print_impl(T&& value, Args&&... args)
	{
		log_stream() << value;
		print_impl(std::forward<Args>(args)...);
	}

	template<LogType log_type, typename ...Args>
	inline void logprint(Args&&...args)
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

//	void logOutput(const LogType, const std::string&);
//	#define PREPARE_LOG(level,params) { std::ostringstream os_; os_ << params << std::endl; logOutput(level,os_.str()); }
#define PREPARE_LOG(x)

	#define EXECUTE_IN_DEBUG(x)		x
	template <typename... Args>
	constexpr inline void LOG_DEBUG(Args&&... args) { logprint<LogType::Debug>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr inline void LOG_INFO(Args&&... args) { logprint<LogType::Info>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr inline void LOG_WARNING(Args&&... args) { logprint<LogType::Warning>(std::forward<Args>(args)...); }
	template <typename... Args>
	constexpr inline void LOG_ERROR(Args&&... args) { logprint<LogType::Error>(std::forward<Args>(args)...); }
	template <typename... Args>
	inline void LOG_CONSTRUCT(Args&&... args) { LOG_DEBUG("Constructing ", " ", std::forward<Args>(args)...); }
	template <typename... Args>
	inline void LOG_DESTRUCT(Args&&... args) { LOG_DEBUG("Constructing ",  " ", std::forward<Args>(args)...); }

	//	#define LOG_CONSTRUCT(x)		LOG_DEBUG("Constructing ", typeid(*this).name(), " ", x)
//	#define LOG_DESTRUCT(x)			LOG_DEBUG("Destroying ", typeid(*this).name(), " ", x)
	#define LOG_CONSTRUCT_NOPARAMS	LOG_CONSTRUCT("")
	#define LOG_DESTRUCT_NOPARAMS	LOG_DESTRUCT("")

	#define __ASSERT(cond,x)		if (!(cond)) LOG_ERROR(x, "\n\tIn file ", __FILE__, " and line: ",__LINE__,"\n\tFunction: ",__FUNCDNAME__ );

#else
	#define EXECUTE_IN_DEBUG(x)	
	#define LOG_DEBUG(x)
	#define LOG_INFO(x)
	#define LOG_WARNING(x)
	#define LOG_ERROR(x)
	#define LOG_CONSTRUCT(x)
	#define LOG_DESTRUCT(x)
	#define LOG_CONSTRUCT_NOPARAMS
	#define LOG_DESTRUCT_NOPARAMS

	#define __ASSERT(cond,x)
#endif
#endif
