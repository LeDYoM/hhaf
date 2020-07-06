#pragma once

#ifndef LOADER_INCLUDE_HPP
#define LOADER_INCLUDE_HPP

#include "loader_export.h"

namespace loader
{
class Loader
{
public:
    Loader();
    ~Loader();

    LOADER_EXPORT void* loadModule(const char* fileName);
    LOADER_EXPORT void* loadMethod(const char* fileName, const char* methodName);
    LOADER_EXPORT bool unloadModule(const char* fileName);

private:
    class LoaderPrivate;
    LoaderPrivate* m_private;
};

LOADER_EXPORT Loader* createLoader();
LOADER_EXPORT void destroyLoader();
}  // namespace loader

#endif
