module;

#include "loader_export.hpp"

export module agloader;

export namespace agl
{
    export class Loader;
    export LOADER_API Loader* createLoader();
    export LOADER_API void destroyLoader();
}
