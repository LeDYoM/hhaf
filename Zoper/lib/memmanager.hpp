#ifndef __LIB_MEMMANAGER_HPP__
#define __LIB_MEMMANAGER_HPP__

#include "compileconfig.hpp"

#ifdef USE_MEM_MANAGER
#define VS_NATIVE_MEMMANAGER

#ifdef VS_NATIVE_MEMMANAGER
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
void installMemManager();
void finishMemManager();

#endif
