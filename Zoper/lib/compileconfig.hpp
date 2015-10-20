#ifndef __LIB_COMPILECONFIG_HPP__
#define __LIB_COMPILECONFIG_HPP__

#ifdef _DEBUG
	#define DEBUG
#endif

#ifdef DEBUG
	#define USE_MEM_MANAGER
	#include "memmanager.hpp"
#endif

#define __USE_LOGS__
#define __MULTITHREAD_LOG__
#define __LOGFILE__		"log.txt"

#endif
