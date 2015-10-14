#ifndef __LIB_LOG_HPP__
#define __LIB_LOG_HPP__

#include "compileconfig.hpp"

#ifdef __USE_LOGS__
	#include <sstream>

	void finishLog();
	void logOutput(const char *);
	#define PREPARE_LOG(params) { std::ostringstream os_; os_ << params << std::endl; logOutput(os_.str().c_str()); }
	#define LOG_DEBUG(x)			PREPARE_LOG(x)
	#define LOG_ERROR(x)			PREPARE_LOG(x)
	#define LOG_CONSTRUCT(x)		LOG_DEBUG("Constructing "<< typeid(*this).name() << " " << x)
	#define LOG_DESTRUCT(x)			LOG_DEBUG("Destroying "<< typeid(*this).name() << " " << x)
	#define LOG_CONSTRUCT_NOPARAMS	LOG_CONSTRUCT("")
	#define LOG_DESTRUCT_NOPARAMS	LOG_DESTRUCT("")

	#define __ASSERT(cond,x)		if (!(cond)) LOG_ERROR(x<< "\n\tIn file "<<__FILE__<< " and line: "<<__LINE__<<"\n\tFunction: "<<__FUNCDNAME__ );

#endif

#endif
