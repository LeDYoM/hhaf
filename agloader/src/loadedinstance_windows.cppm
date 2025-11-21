module;

#if defined(_MSC_VER) || defined(__BORLANDC__)
#define WIN32_LEAN_AND_MEAN
#pragma warning(push)
#pragma warning(disable : 5039)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(pop)

export module agloader.linstance.pfunctions;

export inline void* getMethod(void* handle, const char* methodName)
{
    return static_cast<void*>(
        GetProcAddress(static_cast<HMODULE>(handle), methodName));
}

export inline void* loadSharedObject(const char* fileName)
{
    return static_cast<void*>(LoadLibrary(fileName));
}

export inline bool freeSharedObject(void* handle)
{
    return (FreeLibrary(static_cast<HMODULE>(handle)) != 0);
}

export constexpr char const extension[] = ".dll";
export constexpr char const prefix[]    = "";

#endif
