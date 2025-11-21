#ifdef LINUX
module;

// For now, windows or linux
#include <dlfcn.h>

export module agloader.linstance.pfunctions;

export inline void* getMethod(void* handle, char const* const methodName)
{
    return static_cast<void*>(dlsym(handle, methodName));
}

export inline void* loadSharedObject(char const* const fileName)
{
    return static_cast<void*>(dlopen(fileName, RTLD_LAZY));
}

export inline bool freeSharedObject(void* handle)
{
    return (dlclose(handle) == 0);
}

export constexpr const char* const extension = ".so";
export constexpr const char* const prefix    = "./lib";
#endif
