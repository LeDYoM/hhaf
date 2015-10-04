#ifndef __LIB_LOG_HPP__
#define __LIB_LOG_HPP__

#include "config.h"

#ifdef DEBUG
	void logOutput(const char *);
#include <sstream>

#define PREPARE_LOG(params) { std::ostringstream os_; os_ << params << std::endl; logOutput(os_.str().c_str()); }
	#define LOG_DEBUG(x)	PREPARE_LOG(x)
	#define LOG_ERROR(x)	PREPARE_LOG(x)

#define __ASSERT(cond,x)		if (!cond) LOG_ERROR(x)

#endif

#endif
