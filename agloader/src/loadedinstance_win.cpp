#ifdef LINUX

// For now, windows or linux
#include <dlfcn.h>
inline void* getMethod(void* handle, char const* const methodName)
{
    return static_cast<void*>(dlsym(handle, methodName));
}

inline void* loadSharedObject(char const* const fileName)
{
    return static_cast<void*>(dlopen(fileName, RTLD_LAZY));
}

inline bool freeSharedObject(void* handle)
{
    return (dlclose(handle) == 0);
}

constexpr const char* const extension = ".so";
constexpr const char* const prefix    = "./lib";

#endif
