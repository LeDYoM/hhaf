#include "memmanager.hpp"
#include "compileconfig.hpp"

#ifdef USE_MEM_MANAGER
#ifdef _MSC_VER
#include <windows.h>

static int crtDebugMemAllocHook(int allocType, void *userData, size_t size, int blockType, long requestIndex, const unsigned char *fileName, int lineIndex){

	lineIndex;
	fileName;
	blockType;
	blockType;
	size;
	userData;
	allocType;

	if (requestIndex == 316) //break;

		return true;

	return true;
}

#endif
#endif

void installMemManager()
{
#ifdef USE_MEM_MANAGER
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetAllocHook(crtDebugMemAllocHook);
#endif
#endif
}

void finishMemManager()
{
#ifdef USE_MEM_MANAGER
#ifdef _MSC_VER
//	_CrtDumpMemoryLeaks();
#endif
#endif
}
