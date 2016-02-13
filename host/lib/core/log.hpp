#ifndef __LIB_LOG_HPP__
#define __LIB_LOG_HPP__

#include "compileconfig.hpp"

#ifdef __USE_LOGS__
	#include <sstream>
	enum class LogType
	{
		Debug,
		Info,
		Warning,
		Error,
	};

	void initLog();
	void finishLog();
	void logOutput(const LogType&, const std::string&);
	#define PREPARE_LOG(level,params) { std::ostringstream os_; os_ << params << std::endl; logOutput(level,os_.str()); }
	#define EXECUTE_IN_DEBUG(x)		x
	#define LOG_DEBUG(x)			PREPARE_LOG(LogType::Debug, x)
	#define LOG_INFO(x)				PREPARE_LOG(LogType::Info, x)
	#define LOG_WARNING(x)			PREPARE_LOG(LogType::Warning, x)
	#define LOG_ERROR(x)			PREPARE_LOG(LogType::Error, "Error: " << x)
	#define LOG_CONSTRUCT(x)		LOG_DEBUG("Constructing "<< typeid(*this).name() << " " << x)
	#define LOG_DESTRUCT(x)			LOG_DEBUG("Destroying "<< typeid(*this).name() << " " << x)
	#define LOG_CONSTRUCT_NOPARAMS	LOG_CONSTRUCT("")
	#define LOG_DESTRUCT_NOPARAMS	LOG_DESTRUCT("")

	#define __ASSERT(cond,x)		if (!(cond)) LOG_ERROR(x<< "\n\tIn file "<<__FILE__<< " and line: "<<__LINE__<<"\n\tFunction: "<<__FUNCDNAME__ );
	#define __CHECK(cond,x)		if (!(cond)) LOG_WARNING(x<< "\n\tIn file "<<__FILE__<< " and line: "<<__LINE__<<"\n\tFunction: "<<__FUNCDNAME__ );

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
	#define __CHECK(cond,x)
#endif
void initLog();
void finishLog();
#endif
