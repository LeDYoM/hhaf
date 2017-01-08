#ifndef __LIB_COMPILECONFIG_HPP__
#define __LIB_COMPILECONFIG_HPP__

#include <lib/include/compconfig.hpp>

#ifndef LIB_DEBUG
//	#define USE_MEM_MANAGER

//	#define __USE_LOGS__
//	#define __LOGFILE__		"log.txt"
#else
#define USE_MEM_MANAGER
#define __USE_LOGS__
#define __LOGFILE__		"log.txt"
#define USE_IDE_CONSOLE_FOR_LOGS
#define USE_COUT_FOR_LOGS
#endif



#ifdef USE_MEM_MANAGER
#ifdef LIB_SYSTEM_WINDOWS
	#ifndef _CRTDBG_MAP_ALLOC
		#define _CRTDBG_MAP_ALLOC
	#endif

	#include <stdlib.h>
	#include <crtdbg.h>

	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif
#endif

#endif
