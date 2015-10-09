#include "memmanager.hpp"
#include "compileconfig.hpp"

#ifdef USE_MEM_MANAGER
#ifdef VS_NATIVE_MEMMANAGER
#include <windows.h>
#include <delayimp.h>

static int crtDebugMemAllocHook(int allocType, void *userData, size_t size, int blockType, long requestIndex, const unsigned char *fileName, int lineIndex){

	if (requestIndex == 214) //break;

		return true;

	return true;
}

#endif
#endif

void installMemManager()
{
#ifdef USE_MEM_MANAGER
#ifdef VS_NATIVE_MEMMANAGER
	_CrtSetAllocHook(crtDebugMemAllocHook);
#endif
#endif
}

void finishMemManager()
{
#ifdef USE_MEM_MANAGER
#ifdef VS_NATIVE_MEMMANAGER
	__FUnloadDelayLoadedDLL2("sfml-graphics-d-2.dll");
	__FUnloadDelayLoadedDLL2("sfml-system-d-2.dll");
	__FUnloadDelayLoadedDLL2("sfml-window-d-2.dll");
	
	//_CrtDumpMemoryLeaks();
#endif
#endif
}
