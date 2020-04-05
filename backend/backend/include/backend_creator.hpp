#pragma once

#ifndef LIB_BACKEND_BACKEND_CREATOR_HPP
#define LIB_BACKEND_BACKEND_CREATOR_HPP

#include <backend/include/backendfactory.hpp>

extern "C"
{
    haf::backend::BackendFactory* createBackendFactory();
    void destroyBackendFactory(haf::backend::BackendFactory*);
}

#endif
