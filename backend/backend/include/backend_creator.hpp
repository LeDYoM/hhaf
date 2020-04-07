#pragma once

#ifndef HAF_BACKEND_BACKEND_CREATOR_HPP
#define HAF_BACKEND_BACKEND_CREATOR_HPP

#include <backend/include/backendfactory.hpp>

extern "C"
{
    haf::backend::BackendFactory* createBackendFactory();
    void destroyBackendFactory(haf::backend::BackendFactory*);
}

#endif
